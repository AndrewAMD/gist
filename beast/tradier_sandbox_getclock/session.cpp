#include "session.h"

session::session(asio::io_context& ioc, ssl::context& ctx)
	: 
	resolver_(ioc),
	stream_(ioc, ctx)
{
}

void session::run(
	char const* host,
	char const* port,
	char const* target,
	int version, 
	char const* sandbox_token)
{

		
	// Set SNI Hostname (many hosts need this to handshake successfully)
	if (!SSL_set_tlsext_host_name(stream_.native_handle(), host))
	{
		error_code ec{ static_cast<int>(::ERR_get_error()), asio::error::get_ssl_category() };
		std::cerr << ec.message() << "\n";
		return;
	}

	// Set up an HTTP GET request message
	req_.version(version);
	req_.method(http::verb::get);
	req_.target(target);
	req_.set(http::field::host, host);
	req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
	req_.set(http::field::accept, "application/json");
	req_.set(http::field::authorization, ("Bearer " + (std::string)sandbox_token));


	// Look up the domain name
	auto self{ shared_from_this() };
	resolver_.async_resolve(
		host,
		port,
		[this, self](error_code ec, tcp::resolver::results_type results) {
		return on_resolve(ec, results);
	});
}

void session::on_resolve(
	error_code ec,
	tcp::resolver::results_type results)
{
	if (ec)
		return fail(ec, "resolve");

	auto begin = results.begin();
	auto end = results.end();


	auto self{ shared_from_this() };
	asio::async_connect(
		stream_.lowest_layer(),
		results.begin(),
		results.end(),
		[this, self](error_code ec, tcp::resolver::iterator iterator) {
			on_connect(ec);
	});
}

void session::on_connect(error_code ec)
{
	if (ec)
		return fail(ec, "connect");

	// Perform the SSL handshake
	auto self{ shared_from_this() };
	stream_.async_handshake(
		ssl::stream_base::client,
		[this, self](error_code ec) {
		on_handshake(ec);
	});

}

void session::on_handshake(error_code ec)
{
	if (ec)
		return fail(ec, "handshake");

	// Send the HTTP request to the remote host
	auto self{ shared_from_this() };
	http::async_write(stream_, req_,
		[this, self](error_code ec,	std::size_t bytes_transferred) {
		on_write(ec, bytes_transferred);
	});
}

void session::on_write(
	error_code ec,
	std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "write");

	// Receive the HTTP response
	auto self{ shared_from_this() };
	http::async_read(stream_, buffer_, res_,
		[this, self](error_code ec,	std::size_t bytes_transferred) {
		on_read(ec, bytes_transferred);
	});
}

void
session::on_read(
	error_code ec,
	std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "read");

	std::cout
		<< " *** CHUNKED? ***" << std::endl
		<< res_.chunked() << std::endl << std::endl;

	std::cout
		<< " *** RESULT ***" << std::endl
		<< res_.result() << std::endl << std::endl;
	
	std::cout 
		<< " *** BODY ***" << std::endl
		<< res_.body() << std::endl << std::endl;

	std::cout
		<< " *** ALL ***" << std::endl
		<< res_ << std::endl << std::endl;


	// Gracefully close the stream
	auto self{ shared_from_this() };
	stream_.async_shutdown(
		[this, self](error_code ec) {
		on_shutdown(ec);
	});
}

void session::on_shutdown(error_code ec)
{
	if (ec == asio::error::eof)
	{
		// Rationale:
		// http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
		ec.assign(0, ec.category());
	}
	if (ec)
		return fail(ec, "shutdown");

	// If we get here then the connection is closed gracefully
}





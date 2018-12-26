#pragma once


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _WIN32_WINNT 0x0600 // Windows Vista or newer
#endif


#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;
namespace ssl = asio::ssl;       // from <boost/asio/ssl.hpp>
namespace http = beast::http;    // from <boost/beast/http.hpp>


								 
//------------------------------------------------------------------------------

// Report a failure
void fail(error_code ec, char const* what);
								 
//------------------------------------------------------------------------------


// Performs an HTTP GET and prints the response
class session : public std::enable_shared_from_this<session>
{
	tcp::resolver resolver_;
	ssl::stream<tcp::socket> stream_;
	beast::flat_buffer buffer_; // (Must persist between reads)
	http::request<http::empty_body> req_;
	http::response<http::string_body> res_;

public:
	// Resolver and stream require an io_context
	explicit session(asio::io_context& ioc, ssl::context& ctx);

	// Start the asynchronous operation
	void run(char const* host, char const* port, char const* target, int version, char const* sandbox_token);

	void on_resolve(error_code ec, tcp::resolver::results_type results);

	void on_connect(error_code ec);

	void on_handshake(error_code ec);

	void on_write(error_code ec, std::size_t bytes_transferred);

	void on_read(error_code ec, std::size_t bytes_transferred);

	void on_shutdown(error_code ec);

};
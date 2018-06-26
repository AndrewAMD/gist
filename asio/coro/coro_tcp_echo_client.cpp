#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

												//------------------------------------------------------------------------------

												// Report a failure
void
fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

// Sends a WebSocket message and prints the response
void
do_session(
	std::string const& host,
	std::string const& port,
	std::string const& text,
	asio::io_context& ioc,
	asio::yield_context yield)
{
	boost::system::error_code ec;

	// These objects perform our I/O
	tcp::resolver resolver{ ioc };
	tcp::socket socket{ ioc };

	// Look up the domain name
	auto const results = resolver.async_resolve(host, port, yield[ec]);
	if (ec)
		return fail(ec, "resolve");

	// Make the connection on the IP address we get from a lookup
	for (auto& result : results)
	{
		socket.async_connect(result, yield[ec]);
		if (!ec) break;
	}
	if (ec)
		return fail(ec, "connect");

	std::string msg_out = text;

	// Send the message
	asio::async_write(socket, asio::buffer(std::string(text)), yield[ec]);
	if (ec)
		return fail(ec, "write");

	// This buffer will hold the incoming message
	std::vector<char> b;
	b.resize(msg_out.size()+1);  // room for 
	
	// Read a message into our buffer
	asio::async_read(socket, asio::buffer(b, msg_out.size()), yield[ec]);
	if (ec)
		return fail(ec, "read");

	// Close the WebSocket connection
	socket.close();

	// If we get here then the connection is closed gracefully

	// The buffers() function helps print a ConstBufferSequence
	std::cout << b.data() << std::endl;
}

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	// Check command line arguments.
	if (argc != 4)
	{
		std::cerr <<
			"Usage: websocket-client-coro <host> <port> <text>\n" <<
			"Example:\n" <<
			"    websocket-client-coro echo.websocket.org 80 \"Hello, world!\"\n";
		return EXIT_FAILURE;
	}
	auto const host = argv[1];
	auto const port = argv[2];
	auto const text = argv[3];

	// The io_context is required for all I/O
	asio::io_context ioc;

	// Launch the asynchronous operation
	asio::spawn(ioc, [&](asio::yield_context yield)
	{
		do_session(std::string(host),
			std::string(port),
			std::string(text),
			ioc,
			yield);
	});

	return EXIT_SUCCESS;
}

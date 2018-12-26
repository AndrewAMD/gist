
#include "session.h"

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr <<
			"Usage: getclock.exe <tradier sandbox api token>\n";
		return EXIT_FAILURE;
	}

	auto const host = "sandbox.tradier.com";
	auto const port = "443";
	auto const target = "/v1/markets/clock";
	auto const sandbox_token = argv[1];
	int version = 11;

	// The io_context is required for all I/O
	asio::io_context ioc;

	// The SSL context is required, and holds certificates
	ssl::context ctx{ ssl::context::tlsv12_client };
	ctx.set_verify_mode(asio::ssl::verify_none);

	// Launch the asynchronous operation
	std::make_shared<session>(ioc, ctx)->run(host, port, target, version, sandbox_token);

	// Run the I/O service. The call will return when
	// the get operation is complete.
	ioc.run();

	return EXIT_SUCCESS;
}
#include "session.h"

void fail(error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}
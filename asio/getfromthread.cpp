#include <iostream>
#include <thread>
#include "post_function_use_future.hpp"

namespace asio = boost::asio;

int SayHello()
{
	std::cout << "Hello!" << std::endl;
	return 0;
}

template <typename T>
T GetSum(T a, T b)
{
	std::cout << "Adding " << a << " and " << b << std::endl;
	return a + b;
}

int main() {
	asio::io_context io;
	auto wg = asio::make_work_guard(io);

	std::thread t{ [&] { io.run(); } };
		
	auto res1 = post_function_use_future(io, SayHello);
	res1.get(); // block until return value received.
	
	auto res2 = post_function_use_future(io, []() {return  GetSum(20, 14); });
	std::cout << res2.get() << std::endl; // block until return value received.
	
	wg.reset();
	if(t.joinable()) t.join();
	
	return 0;
}




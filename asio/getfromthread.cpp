#include <iostream>
#include <thread>
#include <functional>
#include "use_future_helpers.hpp"

namespace asio = boost::asio;

int SayHello()
{
	std::cout << "Hello!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}

template <typename T>
T GetSum(T a, T b)
{
	std::cout << "Adding " << a << " and " << b << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return a + b;
}

int main() {
	asio::io_context io;
	auto wg = asio::make_work_guard(io);

	std::thread t{ [&] { io.run(); } };
		
	auto res1 = post_use_future(io, SayHello);
	res1.get(); // block until return value received.
	
	auto res2 = post_use_future(io, []() {return  GetSum(20, 14); });
	std::cout << res2.get() << std::endl; // block until return value received.

	auto res3 = post_use_future(io, (std::function <int()> )std::bind(&SayHello));
	res3.get(); // block until return value received.
	
	asio::steady_timer timer(io);
	timer.expires_from_now(std::chrono::milliseconds(1000));
	auto res4 = async_wait_use_future(timer, [](const boost::system::error_code& ec)
	{
		return (int)ec.value();
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	timer.expires_at(std::chrono::steady_clock::now());
	std::cout << res4.get() << std::endl; // block until return value received.

	wg.reset();
	if(t.joinable()) t.join();
	
	return 0;
}




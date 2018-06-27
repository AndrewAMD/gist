#include <iostream>
#include <thread>
#include <functional>
#include "use_future_helpers.hpp"

namespace asio = boost::asio;
using error_code = boost::system::error_code;
typedef std::function<int()> fu_int;

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

	auto res3 = post_use_future(io, (fu_int)std::bind(&GetSum<int>, 56, -234));
	std::cout << res3.get() << std::endl; // block until return value received.

	asio::steady_timer timer(io);
	timer.expires_from_now(std::chrono::milliseconds(1000));
	auto res4 = async_wait_use_future(timer, [](const error_code& ec)
	{
		return ec;
	});
	error_code ec4 = res4.get(); // block until return value received.
	std::cout << "Code #" << ec4.value() <<": \"" << ec4.message() << "\"" << std::endl; 

	auto res5 = spawn_use_future(io, [&io](asio::yield_context yield)
	{
		error_code ec1;
		asio::steady_timer localtimer(io);
		localtimer.expires_after(std::chrono::milliseconds(1000));
		std::cout << "waiting for 1 sec..." << std::endl;
		localtimer.async_wait(yield[ec1]);
		if (ec1)
			return 200;
		std::cout << "done waiting." << std::endl;

		return 100;
	}
	);
	std::cout << "res5.get(): " << res5.get() << std::endl; // block until return value received.

	wg.reset();
	if(t.joinable()) t.join();
	
	return 0;
}

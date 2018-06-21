#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/use_future.hpp>
#include "lambda_return_type.hpp"
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


template <typename LambdaWithReturnNoArgs, typename ExecutionContext>
auto perform_asyncly(ExecutionContext& ctx, LambdaWithReturnNoArgs f)
{
	using handler_type = typename asio::handler_type
		<asio::use_future_t<>, void(boost::system::error_code, return_type_t<LambdaWithReturnNoArgs>)>::type;

	handler_type handler{ asio::use_future };
	asio::async_result<handler_type> result(handler);

	asio::post(ctx, [handler, f]() mutable {
		handler(boost::system::error_code{}, f());
	});

	return result.get();
}


int main() {
	asio::io_service ios;
	asio::io_service::work wrk{ ios };
	std::thread t{ [&] { ios.run(); } };
		
	auto res1 = perform_asyncly(ios, []() {return  SayHello(); });
	res1.get(); // block until return value received.
	
	auto res2 = perform_asyncly(ios, []() {return  GetSum(20, 14); });
	std::cout << res2.get() << std::endl; // block until return value received.

	ios.stop();
	t.join();

	return 0;
}




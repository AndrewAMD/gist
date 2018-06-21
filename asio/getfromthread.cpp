#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/use_future.hpp>
namespace asio = boost::asio;

template <typename F>
struct return_type_impl;

template <typename R, typename... Args>
struct return_type_impl<R(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(Args..., ...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(*)(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(*)(Args..., ...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(&)(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(&)(Args..., ...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) && > { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) && > { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile&&> { using type = R; };

template <typename T, typename = void>
struct return_type
	: return_type_impl<T> {};

template <typename T>
struct return_type<T, decltype(void(&T::operator()))>
	: return_type_impl<decltype(&T::operator())> {};

template <typename T>
using return_type_t = typename return_type<T>::type;


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

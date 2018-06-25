#ifndef USE_FUTURE_HELPERS_HPP
#define USE_FUTURE_HELPERS_HPP

#include <boost/asio.hpp>
#include "return_type.hpp"

template <typename ExecutionContext, typename FuncWithReturnNoArgs>
auto post_use_future(ExecutionContext& ctx, FuncWithReturnNoArgs f)
{
	using Sig = void(boost::system::error_code, return_type_t<FuncWithReturnNoArgs>);
	using Result = typename asio::async_result<boost::asio::use_future_t<>, Sig>;
	using Handler = typename Result::completion_handler_type;

	Handler handler(std::forward<decltype(boost::asio::use_future)>(boost::asio::use_future));
	Result result(handler);

	boost::asio::post(ctx, [handler, f]() mutable {
		handler(boost::system::error_code(), f());
	});

	return result.get();
}

template <typename TimerType, typename FuncWithReturnEC>
auto async_wait_use_future(TimerType& timer, FuncWithReturnEC f)
{
	using Sig = void(boost::system::error_code, return_type_t<FuncWithReturnEC>);
	using Result = typename asio::async_result<boost::asio::use_future_t<>, Sig>;
	using Handler = typename Result::completion_handler_type;

	Handler handler(std::forward<decltype(boost::asio::use_future)>(boost::asio::use_future));
	Result result(handler);

	timer.async_wait([handler, f](const boost::system::error_code& ec) mutable {
		handler(boost::system::error_code(), f(ec));
	});

	return result.get();
}

#endif

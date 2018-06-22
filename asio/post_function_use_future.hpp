#ifndef POST_FUNCTION_USE_FUTURE
#define POST_FUNCTION_USE_FUTURE

#include <boost/asio.hpp>
#include "function_return_type.hpp"

template <typename ExecutionContext, typename FuncWithReturnNoArgs>
auto post_function_use_future(ExecutionContext& ctx, FuncWithReturnNoArgs f)
{
	using handler_type = typename boost::asio::handler_type
		<boost::asio::use_future_t<>, void(boost::system::error_code, return_type_t<FuncWithReturnNoArgs>)>::type;

	handler_type handler{ boost::asio::use_future };
	boost::asio::async_result<handler_type> result(handler);

	boost::asio::post(ctx, [handler, f]() mutable {
		handler(boost::system::error_code{}, f());
	});

	return result.get();
}

#endif

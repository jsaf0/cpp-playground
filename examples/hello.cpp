
#include "boost/asio/detached.hpp"
#include "boost/asio/steady_timer.hpp"
#include "boost/async/op.hpp"
#include "boost/async/task.hpp"
#include "boost/async/this_thread.hpp"
#include "fmt/format.h"
#include <exception>
#include <fmt/core.h>
#include <boost/asio/io_context.hpp>
#include <boost/async/promise.hpp>
#include <boost/async/spawn.hpp>
#include <source_location>
#include <stdexcept>
#include <chrono>

using namespace std::chrono_literals;

class my_class {
public:
    int val{123};

    ~my_class() { fmt::println("bye bye {}", __func__); }

    boost::async::promise<int> get_value() {
        boost::asio::steady_timer t{boost::async::this_thread::get_executor(), 10ms};
        co_await t.async_wait(boost::async::use_op);
        fmt::println("after wait {} {}\n", fmt::ptr(this), this->val);
        co_return val;
    }
};

boost::async::promise<void> hello()
{
    fmt::print("Hello from {}\n", __FUNCTION__);
    co_return;
}

boost::async::task<void> co_main()
{
    auto mc = std::make_unique<my_class>();
    //+mc->get_value();
    fmt::println("v = {}", co_await mc->get_value());
    co_await hello();
}

int main(int, char**)
{
    fmt::print("Hello, world\n");
    boost::asio::io_context ctx{1u};
    boost::async::this_thread::set_executor(ctx.get_executor());
    
    boost::async::spawn(ctx.get_executor(), co_main(), [](std::exception_ptr e) {
        if (e)
            std::rethrow_exception(e);
    });

    try {
        ctx.run();
    } catch (const std::exception& e) {
        fmt::println("Ended with: {}", e.what());
    }

    return 0;
}

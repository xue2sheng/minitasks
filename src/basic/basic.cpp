#include <czmq++/czmqpp.hpp>
#include "basic.hpp"

int basic(int x) 
{ 
    auto test_cb = [](czmqpp::socket& pipe)
    {
        char *ping = zstr_recv(pipe.self());
        zstr_free(&ping);
        zstr_send(pipe.self(), "pong");
    };
    czmqpp::context ctx;
    assert(ctx.self());
    czmqpp::socket pipe = thread_fork(ctx, test_cb);
    assert(pipe.self());
    zstr_send(pipe.self(), "ping");
    char *pong = zstr_recv(pipe.self());
    assert(streq(pong, "pong"));
    zstr_free(&pong);

 return 1 + x; 
}  

int extra(int y)
{
    return 13*y;
}
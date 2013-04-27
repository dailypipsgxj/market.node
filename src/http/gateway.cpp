#include "native/loop.hpp"
#include "native/tcp.hpp"
#include "native/http.hpp"

#include <vector>
#include <iostream>

namespace node = native::http;

int main(int argc, char *argv[]) {
    node::http server;
    if(!server.listen("127.0.0.1", 8080, [&](node::request& req, node::response& res) {
        res.set_status(200);
        res.set_header("Content-Type", "text/html");
        res.end("Hey!"); 
    })) {
        std::cerr << "Failed to start server." << std::endl;
        return 1;
    }
    return native::run();
}

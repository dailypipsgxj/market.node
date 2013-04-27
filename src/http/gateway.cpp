#include "node/loop.hpp"
#include "node/tcp.hpp"
#include "node/http.hpp"

#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    market::node::http::http server;
    if(!server.listen("127.0.0.1", 8080, [&](market::node::http::request& req, market::node::http::response& res) {
        res.set_status(200);
        res.set_header("Content-Type", "text/html");
        res.end("Hey!"); 
    })) {
        std::cerr << "Failed to start server." << std::endl;
        return 1;
    }
    return market::node::run();
}

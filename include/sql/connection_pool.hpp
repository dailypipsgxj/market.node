#pragma once
#include <market_types.hpp>

class ConnectionPool { 
    public:
        ConnectionPool(uint32_t max_connections);
        SharedConnectionPtr getConnection();
        void releaseConnection(SharedConnectionPtr con);
    private:
        std::vector<SharedConnectionPtr> free_connections;
        SharedConnectionPtr createConnection();
};

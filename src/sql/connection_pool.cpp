//
// connection_pool.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Alex Caudill (alex at furosys.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <vector>
#include <market_config.hpp>
#include <market_types.hpp>
#include <connection_pool.hpp>

const std::string database(DATABASE);
const std::string url(DBHOST);
const std::string user(USER);
const std::string password(PASSWORD);

ConnectionPool::ConnectionPool(uint32_t max_connections) {
    for (uint32_t i = 0; i < max_connections; i++) {
        SharedConnectionPtr con = createConnection();
        free_connections.push_back(con);
    }
}

SharedConnectionPtr ConnectionPool::getConnection() {
    if ( free_connections.size() > 0 ) {
        SharedConnectionPtr con = *(free_connections.end() - 1);
        free_connections.pop_back();
        return con;
    } else { 
        return createConnection();
    }
}

void ConnectionPool::releaseConnection(SharedConnectionPtr con) {
    free_connections.push_back(con);
}

SharedConnectionPtr ConnectionPool::createConnection() {
    try {
        sql::Driver *driver;
        driver = get_driver_instance();
        auto con = std::shared_ptr<sql::Connection>(driver->connect(url, user, password));
        con->setSchema(database);
        return con;
    } catch (sql::SQLException) {
        std::cout << "Failed to connect to database. Exiting..." << std::endl;
        exit(1);
    }
}

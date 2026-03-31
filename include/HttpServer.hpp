// HttpServer.hpp

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <memory>

namespace http_server {

class HttpServer {
public:
    HttpServer(boost::asio::io_context& ioc, port_t port);
    void run();

private:
    void do_accept();
    void on_accept(boost::beast::error_code ec);

    boost::asio::ip::tcp::acceptor acceptor_;
    // Add other members as needed for managing connections, requests, etc.
};

} // namespace http_server

#endif // HTTPSERVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;      // from <boost/beast.hpp>
namespace http = beast::http;          // from <boost/beast/http.hpp>
namespace net = boost::asio;           // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;      // from <boost/asio/ip/tcp.hpp>

// This function converts a binary string to a hex string
std::string to_hex(const std::string& input) {
    std::ostringstream oss;
    for (unsigned char c : input) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return oss.str();
}

// This function handles incoming requests for GET and POST
void handle_request(http::request<http::string_body> req, tcp::socket& socket) {
    http::response<http::string_body> res;
    res.set(http::field::server, "Boost.Beast");
    res.set(http::field::version, req.version());

    switch (req.method()) {
        case http::verb::get: {
            res.result(http::status::ok);
            res.set(http::field::content_type, "text/plain");
            res.body() = "GET request received!\n";
            break;
        }
        case http::verb::post: {
            // Process POST request
            res.result(http::status::ok);
            res.set(http::field::content_type, "text/plain");
            res.body() = "POST request received with body: " + req.body() + "\n";
            break;
        }
        default:
            res.result(http::status::bad_request);
            res.body() = "Unsupported request method.\n";
            break;
    }
    // Send the response
    http::write(socket, res);
}

// This function starts the server and listens for connections
void run_server(unsigned short port) {
    net::io_context ioc;
    tcp::acceptor acceptor(ioc, {tcp::v4(), port});

    while (true) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        beast::flat_buffer buffer;
        http::request<http::string_body> req;

        // Read the request
        http::read(socket, buffer, req);
        handle_request(std::move(req), socket);
    }
}

int main() {
    try {
        unsigned short port = 8080;
        run_server(port);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
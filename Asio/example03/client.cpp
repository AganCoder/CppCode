#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/array.hpp>
#include <boost/asio/ssl.hpp>

using namespace std;
using namespace boost;
using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;


int main(int argc, char** argv)
{
    // SSL 编程
    boost::asio::io_context io_context;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
    ssl_socket socket(io_context, ssl_context); 
    
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("google.com", "443");

    boost::asio::connect(socket.next_layer(), endpoints);

    // 同步方式
    socket.handshake(boost::asio::ssl::stream_base::client);

    // 异步方式
    // socket.async_handshake(boost::asio::ssl::stream_base::client, [&](boost::system::error_code, error) {

    // });
    char request[] = 
        "GET / HTTP/1.1\n"
        "Host: www.google.com\n"
        "Connection: close\n\n";

    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf response;
    boost::system::error_code ec;
    boost::asio::read(socket, response, ec);

    std::cout << std::istream(&response).rdbuf() << std::endl;

    return EXIT_SUCCESS;
}
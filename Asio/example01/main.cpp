#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char** argv)
{
    try {
        std::cout << "server start ." << std::endl;
        boost::asio::io_service ios;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 13659);
        boost::asio::ip::tcp::acceptor acceptor(ios, endpoint);

        std::cout << "addr: " << acceptor.local_endpoint().address() << std::endl;
        std::cout << "port: " << acceptor.local_endpoint().port() << std::endl;
    } catch (...) {
        std::cout << "server exceptional" << std::endl;
    }

    std::cout << "server end." << std::endl;
    getchar();

    return EXIT_SUCCESS;
}
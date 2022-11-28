#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char** argv)
{
    try {
        std::cout << "server start ." << std::endl;

        // asio程序必须的io_service对象
        boost::asio::io_service ios;

        // 具体的服务器地址与端口
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 13659);

        // 创建acceptor对象，当前的IPV4作为服务器地址(127.0.0.1 || 0.0.0.0)，接受端口13695的消息.        
        boost::asio::ip::tcp::acceptor acceptor(ios, endpoint);

        // 打印当前服务器地址
        std::cout << "addr: " << acceptor.local_endpoint().address() << std::endl;

        // 打印当前服务器端口
        std::cout << "port: " << acceptor.local_endpoint().port() << std::endl;
    } catch (...) {
        std::cout << "server exceptional" << std::endl;
    }

    std::cout << "server end." << std::endl;
    getchar();

    return EXIT_SUCCESS;
}
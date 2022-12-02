#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

class Server {
private:
    // 服务器 io 上下文
    boost::asio::io_service &ios_;   

    // 接收器实例
    boost::asio::ip::tcp::acceptor acceptor_;

    // socket 智能指针
    typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

    std::string buffer;
    
public:
    Server(boost::asio::io_service& _ios): ios_(_ios), acceptor_(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13569)), buffer(1000, '\0') {
        start();
    }

    void start(void) {
        socket_ptr socket(new boost::asio::ip::tcp::socket(ios_));
        acceptor_.async_accept(*socket, boost::bind(&Server::accept_handler, this, boost::asio::placeholders::error, socket));
    }

    // 请求者响应后触发的处理器
	void accept_handler(const boost::system::error_code& _ec, socket_ptr _socket) {
		// 错误码检测
		if (_ec) {
			return;
		}
		// 打印当前连接进来的客户端
		std::cout << "client: " << _socket->remote_endpoint().address() << std::endl;
    
		// 异步发送 "hello CSND_Ayo" 消息到客户端，发送成功后，自动调用Server::write_handler函数
		_socket->async_write_some(boost::asio::buffer("hello CSND_Ayo"),
			boost::bind(&Server::write_handler, this,
			boost::asio::placeholders::error, _socket));

        std::string buffer(1000, '\0');
        
        start();
	}

    void read_hanlder(const boost::system::error_code& error, std::size_t bytes_transferred, socket_ptr _socket)
    {
        std::cout << "read_hanlder size "  << bytes_transferred << std::endl;

        // 异步发送 "hello CSND_Ayo" 消息到客户端，发送成功后，自动调用Server::write_handler函数
		_socket->async_write_some(boost::asio::buffer("hello CSND_Ayo"),
			boost::bind(&Server::write_handler, this,
			boost::asio::placeholders::error, _socket));

    }    
    
	// 完成异步写操作后的处理器
	void write_handler(const boost::system::error_code& _ec, socket_ptr _socket) {        
		std::cout << "server: send message complete." << std::endl;

        _socket->async_read_some(boost::asio::buffer(buffer), boost::bind(&Server::read_hanlder, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, _socket));
	}
};

int main(int argc, char** argv)
{
    try {
        std::cout << "server start ." << std::endl;

        // asio程序必须的io_service对象
        boost::asio::io_service ios;    
        Server serve(ios);

        ios.run();
        
    } catch (std::exception& _e) {
        std::cout << "server exceptional." << std::endl;
		std::cout << _e.what() << std::endl;
    }

    std::cout << "server end." << std::endl;
    getchar();

    return EXIT_SUCCESS;
}
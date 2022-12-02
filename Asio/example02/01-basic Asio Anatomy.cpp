#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/array.hpp>

using namespace std;
using namespace boost;

int main(int argc, char** argv)
{
    asio::io_context io_context;
    asio::ip::tcp::socket socket(io_context);
    boost::system::error_code ec;

    socket.connect(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13569), ec);
    if( ec )
    {
        cout << "connect error " << ec.message() << endl;
        return EXIT_FAILURE;
    }
    cout << "local port: " << socket.local_endpoint().port() << endl;    
    
    for(;;)
    {   
        // 如果使用 string, 一定要初始化大小
        std::string in(100, '\0');
        boost::array<char, 128> buffer;
        boost::system::error_code error;

        std::size_t len = socket.read_some(asio::buffer(in), error);

        if( error == boost::asio::error::eof)
        {
            break;
        }
        else if( error )
        {
            cout << "there are some error " << error.message() << endl;
            break;

        }
        cout << in.data() << ", len = " << len << endl;
        // cout << "收到的消息" << len << "message = : " <<  msg << ", ec = " << ec.value() << ", msg = " << ec.message() << endl;


        string msg;
        cin >> msg;

        socket.write_some(asio::buffer(msg));
    }

    socket.close();

    return EXIT_SUCCESS;
}
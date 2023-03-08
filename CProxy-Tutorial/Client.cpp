#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

int main(int argc, char const *argv[])
{
    std::string writeBuffer = "1234567890";
    std::vector<char> readBuffer(1024);

    int ret = 0;
    ssize_t size = 0;
 
    // 创建 fd
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);   

    // 连接 connect
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_aton("127.0.0.1", &addr.sin_addr);

    socklen_t length = sizeof(struct sockaddr_in);

    if( (ret = connect(sockfd, (struct sockaddr *)&addr, length)) != 0 )
    {
        std::cout << "error on connect" << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    // 读写数据
    std::cout << "input data: ";
    std::cin >> writeBuffer;

    if( (size = write(sockfd, writeBuffer.data(), writeBuffer.length())) != writeBuffer.length() )
    {
        std::cout << "error on write" << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    size = read(sockfd, &readBuffer[0], readBuffer.size());
    if( size == -1)
    {
        std::cout << "error on read " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    } 
    else if (size == 0 ) 
    {
        std::cout << "no data read, read end-of-file" << std::endl;
    } 
    else
    {
        // std::string recv(readBuffer.cbegin(), readBuffer.cend()); // won't clear readBuffer data 
        std::string recv(readBuffer.cbegin(), readBuffer.cbegin() + size);
        std::cout << "read data: " << recv << ", size = " << size << std::endl;        
    }

    return 0;
}
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <sys/select.h>

int main(int argc, char const *argv[])
{   
    std::vector<int> fds;
    fd_set readSet;

    // 1. 创建一个 sockfd 对象;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 绑定到对应端口
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_aton("127.0.0.1", &server_addr.sin_addr);
    if( bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0 )
    {
        std::cout << "bind failed, " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    // 3. 开始监听
    if( listen(sockfd, 10) != 0 )
    {
        std::cout << "listen failed, " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }    

    // 4. 接收数据, 读写数据   
    int acceptfd = 0;    
    socklen_t socketlen = sizeof(struct sockaddr_in);   
    fds.push_back(sockfd);

    for(;;)
    {
        // clear readSet
        FD_ZERO(&readSet);        
        // set fd_Set before select 
        for(auto it = fds.cbegin(); it != fds.cend(); it++)
        {
            FD_SET(*it, &readSet);
        }

        // start select
        int retval = select(FD_SETSIZE, &readSet, NULL, NULL, NULL);
        if( retval >= 0 )
        {
            // check if is socketfd
            if( FD_ISSET(sockfd, &readSet) )
            {
                acceptfd = accept(sockfd, (struct sockaddr *)&server_addr, &socketlen);
                if( acceptfd >= 0 )
                {
                    // fds.erase(std::remove(fds.begin(), fds.end(), sockfd),  fds.end());
                    fds.push_back(acceptfd);
                }
                else
                {
                    std::cout << "accept failed" << std::endl;
                }   
                std::cout << "accept fd = " << acceptfd << ", fds.size() = " << fds.size() << std::endl;
                retval--;     
            } 
            
            std::vector<int> readedfds;
            for(auto it = fds.begin(); it != fds.end() && retval > 0; ++it)
            {
                if( FD_ISSET(*it, &readSet) )
                {                                        
                    std::vector<char> readBuffer(1024);
                    int size = read(acceptfd, &readBuffer[0], readBuffer.size());
                    if( size == -1)
                    {
                        std::cout << "error on read " << strerror(errno) << std::endl;
                    } 
                    else if (size == 0 ) 
                    {
                        std::cout << "no data read, read end-of-file " << *it << std::endl;        
                    } 
                    else
                    {
                        // std::string recv(readBuffer.cbegin(), readBuffer.cend()); // won't clear readBuffer data 
                        std::string recv(readBuffer.cbegin(), readBuffer.cbegin() + size);
                        std::cout << recv  << std::endl;        

                        // TODO: write should be here, This is just for simple reply
                        if( write(acceptfd, recv.c_str(), recv.size()) != size )
                        {
                            std::cout << "error on write" << strerror(errno) << std::endl;
                        }                       
                    } 
                    FD_CLR(*it, &readSet);                    
                    retval--;

                    readedfds.push_back(*it);
                }
            }

            for( auto it = readedfds.cbegin(); it != readedfds.cend(); ++it)
            {                
                fds.erase(std::remove(fds.begin(), fds.end(),  *it),  fds.end());            
                close(*it);
            }
        }
    }

    return 0;
}

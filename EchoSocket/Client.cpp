#include "Client.h"

#include <cstdio>
#include <cstring>
#include <sys/unistd.h>

Client::Client() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _addr.sin_port = htons(9092);
}

Client::~Client() {
    close(_sockfd);
}

void Client::Connect() {
    if(int err = connect(_sockfd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr))) {
        perror("client error: ");
    }

    while(true){
        char buf[1024];     //定义缓冲区
        bzero(&buf, sizeof(buf));       //清空缓冲区
        scanf("%s", buf);             //从键盘输入要传到服务器的数据
        ssize_t write_bytes = write(_sockfd, buf, sizeof(buf));      //发送缓冲区中的数据到服务器socket，返回已发送数据大小
        if(write_bytes == -1){          //write返回-1，表示发生错误
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        bzero(&buf, sizeof(buf));       //清空缓冲区
        ssize_t read_bytes = read(_sockfd, buf, sizeof(buf));    //从服务器socket读到缓冲区，返回已读数据大小
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }else if(read_bytes == 0){      //read返回0，表示EOF，通常是服务器断开链接，等会儿进行测试
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){     //read返回-1，表示发生错误，按照上文方法进行错误处理
            close(_sockfd);
            perror("socket error:");
        }
    }

}

int main() {
    const auto client = new Client();
    client->Connect();
    delete client;
    return 0;
}


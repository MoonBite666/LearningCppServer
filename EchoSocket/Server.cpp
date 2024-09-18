#include "Server.h"

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

Server::Server() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&_addr,sizeof(_addr));

    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _addr.sin_port = htons(9092);

    if(int err = bind(_sockfd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr))) {
        perror("Socket init failed: ");
        exit(EXIT_FAILURE);
    }
    listen(_sockfd,SOMAXCONN);
}

Server::~Server() {
    close(_sockfd);
}

void Server::waitConnection() const {
    printf("Waiting for Client......");
    sockaddr_in client_addr{};
    socklen_t addr_len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));

    const int client_sockfd = accept(_sockfd, reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
    printf("new client fd %d! IP: %s Port: %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while (true) {
        char buf[1024];     //定义缓冲区
        bzero(&buf, sizeof(buf));       //清空缓冲区
        ssize_t read_bytes = read(client_sockfd, buf, sizeof(buf)); //从客户端socket读到缓冲区，返回已读数据大小
        if(read_bytes > 0){
            printf("message from client fd %d: %s\n", client_sockfd, buf);
            write(client_sockfd, buf, sizeof(buf));           //将相同的数据写回到客户端
        } else if(read_bytes == 0){             //read返回0，表示EOF
            printf("client fd %d disconnected\n", client_sockfd);
            close(client_sockfd);
            break;
        } else if(read_bytes == -1){        //read返回-1，表示发生错误，按照上文方法进行错误处理
            close(client_sockfd);
            perror("socket error:");
        }
    }
}


int main() {
    auto server = new Server();
    server->waitConnection();
    delete server;
    return 0;
}
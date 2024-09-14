#include "Server.h"

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

Server* server = nullptr;

void signalHandler(int signum) {
    if(server) {
        delete server;
        server = nullptr;
    }
    exit(signum);
}

Server::Server() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&_addr,sizeof(_addr));

    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _addr.sin_port = htons(9091);

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
    printf("Waiting for Client......\n");
    sockaddr_in client_addr{};
    socklen_t addr_len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));

    const int client_sockfd = accept(_sockfd, reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
    printf("new client fd %d! IP: %s Port: %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    char buf[1024];
    while(true) {
        bzero(&buf,sizeof(buf));
        scanf("%s", buf);

        if(ssize_t read_bytes = read(client_sockfd, buf, sizeof(buf)); read_bytes > 0) {
            printf("message from client fd %d: %s\n", client_sockfd, buf);
            write(client_sockfd, buf, sizeof(buf));
        }
        else if (read_bytes == 0) {
            printf("client fd %d disconnected\n", client_sockfd);
            break;
        }
        else {
            perror("socket error:");
            break;
        }
    }
}


int main() {
    signal(SIGINT, signalHandler);
    server = new Server();
    server->waitConnection();
    delete server;
    return 0;
}
#include "Client.h"

#include <cstdio>
#include <cstring>
#include <sys/unistd.h>

Client::Client() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _addr.sin_port = htons(9090);
}

Client::~Client() {
    close(_sockfd);
}

void Client::Connect() {
    if(int err = connect(_sockfd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr))) {
        perror("client error: ");
    }
}

int main() {
    const auto client = new Client();
    client->Connect();
    delete client;
    return 0;
}


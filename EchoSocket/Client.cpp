#include "Client.h"

#include <cstdio>
#include <cstring>
#include <sys/unistd.h>

Client::Client() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _addr.sin_port = htons(9091);
}

Client::~Client() {
    close(_sockfd);
}

void Client::Connect() {
    if(int err = connect(_sockfd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr))) {
        perror("client error: ");
    }
    char buf[1024];
    while(true) {
        bzero(&buf,sizeof(buf));

        if(ssize_t write_bytes = write(_sockfd,buf,sizeof(buf)); write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        bzero(buf, sizeof(buf));
        ssize_t read_bytes = read(_sockfd, buf, sizeof(buf));
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            close(_sockfd);
            perror("socket read error");
        }
    }
}

int main() {
    const auto client = new Client();
    client->Connect();
    delete client;
    return 0;
}


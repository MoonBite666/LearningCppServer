#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>

class Server {
public:
    Server();
    ~Server();
    void waitConnection() const;

private:
    int _sockfd;
    sockaddr_in _addr{};
};

#endif //SERVER_H

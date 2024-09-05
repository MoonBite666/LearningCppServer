#ifndef CLIENT_H
#define CLIENT_H
#include <arpa/inet.h>

class Client {
public:
    Client();
    ~Client();
    void Connect();
private:
    int _sockfd;
    sockaddr_in _addr{};
};

#endif //CLIENT_H

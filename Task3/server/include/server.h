#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <ubacipc/TCPServer.h>
#include <iostream>
#include <unordered_set>
#include<thread>

class Server : public UBACIPC::TCPServer {
public:
    Server(int port);
    ~Server();

    virtual void createNewClient(int fd) override;
    void handleClientMessage(int senderFd, std::string& msg);

    std::unordered_set<int> clientFds;
};

#endif
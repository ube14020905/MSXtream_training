#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <ubacipc/TCPServer.h>

class EchoServer : public UBACIPC::TCPServer {
public:
    EchoServer(int port);
    virtual ~EchoServer();
    virtual void createNewClient(int fd) override;
};

#endif

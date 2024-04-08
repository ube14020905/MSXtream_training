#include "echo_server.h"

void EchoServer::createNewClient(int fd) {
    std::cout << "New client connected: " << fd << std::endl;
    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(fd, buffer, sizeof(buffer), 0)) > 0) {
        std::cout<<"Received from client: "<<buffer<<std::endl;
        send(fd, buffer, bytesRead, 0);
    }

    std::cout << "Client disconnected: " << fd << std::endl;
    close(fd);
}

EchoServer::EchoServer(int port) : TCPServer(port) {}

EchoServer::~EchoServer() {}
#include "echo_server.h"

void EchoServer::createNewClient(int fd) {
    std::cout << "New client connected: " << fd << std::endl;
    char buffer[1024];
    int bytesRead;

    while (true) {
        bytesRead = recv(fd, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::cout << "Received from client: " << buffer << std::endl;
            int bytesSent = send(fd, buffer, bytesRead, 0);
            if (bytesSent != bytesRead) {
                std::cerr << "Error sending data to client" << std::endl;
                break;
            }
        } else if (bytesRead == 0) {
            std::cout << "Client disconnected: " << fd << std::endl;
            close(fd);
            break;
        } else {
            std::cerr << "Error receiving data from client" << std::endl;
            break;
        }
    }
}

EchoServer::EchoServer(int port) : TCPServer(port) {}

EchoServer::~EchoServer() {}
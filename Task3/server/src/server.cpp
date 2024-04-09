#include "server.h"

void Server::handleClientMessage(int senderFd, std::string& msg) {
    for (int clientFd : clientFds) {
        if (clientFd != senderFd) {
            int bytesSent = send(clientFd, msg, msg.length(),0);
            if (bytesSent<0) {
                std::cerr << "Error sending data to client" << std::endl;
            }
        }
    }
}

void handleClient(Server* server, int fd) {
    std::cout << "New client connected: " << fd << std::endl;
    server->clientFds.insert(fd);

    char buffer[1024];
    ssize_t bytesRead;

    while (true) {
        bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            std::string msg(buffer, bytesRead);
            std::cout << "Received from client: " << msg << std::endl;
            server->handleClientMessage(fd, msg);
        } else if (bytesRead == 0) {
            std::cout << "Client disconnected: " << fd << std::endl;
            server->clientFds.erase(fd);
            close(fd);
            break;
        } else {
            std::cerr << "Error receiving data from client" << std::endl;
            server->clientFds.erase(fd);
            close(fd);
            break;
        }
    }
}

void Server::createNewClient(int fd) {
    std::thread t(handleClient, this, fd);
    t.detach();
}

Server::Server(int port) : TCPServer(port) {}

Server::~Server() {}

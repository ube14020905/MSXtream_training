#include "client.h"

client::client(std::string ip, int port) : TCPClient(ip, port) {}

void client::start() {
    std::string msg;
    while (true) {
        std::cout << "Enter a message or (type 'exit' to exit): ";
        std::getline(std::cin, msg);
        if (msg == "exit") {
            break;
        }
        int bytesSent = sendData(msg);
        if (bytesSent > 0) {
            std::cout << "Message sent" << std::endl;
            char buffer[1024];
            int bytesRead = recv(this->getDescriptor(), buffer, sizeof(buffer), 0);
            std::cout<<bytesRead<<std::endl;
            if (bytesRead > 0) {
                std::cout << "Received from server: " << buffer << std::endl;
            } else {
                std::cerr << "Error receiving response from server" << std::endl;
            }
        } else {
            std::cerr << "Error sending message" << std::endl;
        }
    }
}

client::~client() {}
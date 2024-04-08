#include "echo_server.h"

int main() {
    EchoServer server(8080);
    while(true){
    server.acceptClientConnection();
    }
    return 0;
}

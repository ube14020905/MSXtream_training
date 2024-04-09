#include "server.h"

int main() {
    Server server(8080);
    while(true){
    server.acceptClientConnection();
    }
    return 0;
}

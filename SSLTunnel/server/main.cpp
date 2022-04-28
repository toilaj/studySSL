#include "TlsServer.h"

int main() {
    TlsServer server(8080);
    char buffer[BUFFER_SIZE] = {0};
    if(!server.Init()) {
        cout << "server init failed" << endl;
        exit(1);
    }
    if(!server.HandShake()) {
        cout << "handshake failed" << endl;
        exit(1);
    }
    while(true) {
        if(-1 == server.Read(buffer, sizeof(buffer), true)) {
            break;
        }
        cout << buffer << endl;
    }
    return 0;
}
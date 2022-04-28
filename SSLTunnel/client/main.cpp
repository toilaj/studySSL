//
// Created by Joe_Jing on 2022/4/28.
//

#include "TlsClient.h"

int main() {
    string addr = "127.0.0.1";
    char buffer[BUFFER_SIZE] = {0};
    TlsClient client(addr, 8080);
    if(false == client.Init()) {
        cout << "client init failed" << endl;
        exit(1);
    }
    if(false == client.HandShake()) {
        cout << "handshake failed" << endl;
        exit(1);
    }
    while(true) {
        cin >> buffer;
        if( -1 == client.Write(buffer, ::strlen(buffer), true)) {
            break;
        }
    }
    return 0;
}
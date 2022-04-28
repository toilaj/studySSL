//
// Created by Joe_Jing on 2022/4/28.
//

#ifndef SSLTUNNEL_TLSCLIENT_H
#define SSLTUNNEL_TLSCLIENT_H

#include "../common/TlsSocket.h"

class TlsClient : public TlsSocket {
public:
    TlsClient(string &Address, uint16_t Port) {
        inet_pton(AF_INET, Address.c_str(), &m_ServerAddress.sin_addr);
        m_ServerAddress.sin_port = htons(Port);
        m_ServerAddress.sin_family = AF_INET;
    };
    ~TlsClient() override {
        CleanupOpenSSL();
        CloseSocket();
    };
    bool HandShake() override;
    bool Init() override;
private:
    sockaddr_in m_ServerAddress{};
    int m_fd{};
    SSL *m_Ssl{};
};


#endif //SSLTUNNEL_TLSCLIENT_H

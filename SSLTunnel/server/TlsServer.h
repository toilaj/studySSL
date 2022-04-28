//
// Created by Joe_Jing on 2022/4/28.
//

#ifndef SSLTUNNEL_TLSSERVER_H
#define SSLTUNNEL_TLSSERVER_H


#include "../common/TlsSocket.h"

class TlsServer : public TlsSocket{
public:
    explicit TlsServer(uint16_t Port) {
        m_ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        m_ServerAddress.sin_port = htons(Port);
        m_ServerAddress.sin_family = AF_INET;
    };
    ~TlsServer() override {
        CleanupOpenSSL();
        CloseSocket();
    };
    bool HandShake() override;
    bool Init() override;
private:
    sockaddr_in m_ServerAddress{};
    sockaddr_in m_ClientAddress{};
    int m_fd{};
    int m_client_fd{};
    SSL *m_Ssl{};
};


#endif //SSLTUNNEL_TLSSERVER_H

//
// Created by Joe_Jing on 2022/4/28.
//
#ifndef SSLTUNNEL_TLSSOCKET_H
#define SSLTUNNEL_TLSSOCKET_H
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>

using namespace std;
#define BUFFER_SIZE 4096

class TlsSocket {
public:
    TlsSocket() = default;
    virtual ~TlsSocket() = default;
    virtual bool  Init();
    void CloseSocket();
    void CleanupOpenSSL();
    virtual bool HandShake() = 0;
    int Write(const char *buf, uint64_t n, bool right_now);
    int Read(char *buf, uint64_t n, bool right_now);
    SSL *GetSsl() {
        return m_Ssl;
    }
    SSL_CTX *GetSslCtx() {
        return m_SslCtx;
    }
    int GetSocket() const {
        return m_fd;
    }
    const char* CERT_FILE = "./cert.pem";
    const char* KEY_FILE = "./key.pem";
private:
    bool CreateSocket();
    bool InitOpenSsl();
    bool CreateSslCtx();
    int m_fd{};
    SSL_CTX *m_SslCtx{};
    SSL *m_Ssl{};
};


#endif //SSLTUNNEL_TLSSOCKET_H

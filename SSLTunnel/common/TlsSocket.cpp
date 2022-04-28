//
// Created by Joe_Jing on 2022/4/28.
//

#include <unistd.h>
#include "TlsSocket.h"

bool TlsSocket::Init() {
    bool ret = false;
    ret |= CreateSocket();
    ret |= InitOpenSsl();
    return ret;
}

bool TlsSocket::CreateSocket() {
    m_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    cout << "create socket fd = " << m_fd << endl;
    if(m_fd < 0) {
        return false;
    }
    return true;
}

bool TlsSocket::InitOpenSsl() {
    bool ret;
    ret = CreateSslCtx();
    if(!ret) {
        return false;
    }
    SSL_CTX_set_ecdh_auto(m_SslCtx, 1);
    /* Set the key and cert */

    if (SSL_CTX_use_certificate_file(m_SslCtx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    if (SSL_CTX_use_PrivateKey_file(m_SslCtx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    m_Ssl = SSL_new(m_SslCtx);
    if(m_Ssl == nullptr) {
        return false;
    }
    return true;
}

bool TlsSocket::CreateSslCtx() {
    const SSL_METHOD *method;

    method = TLS_method();
    m_SslCtx = SSL_CTX_new(method);
    if(m_SslCtx == nullptr) {
        return false;
    }
    return true;
}

void TlsSocket::CloseSocket()
{
    ::close(m_fd);
}

void TlsSocket::CleanupOpenSSL()
{
    SSL_CTX_free(m_SslCtx);
    EVP_cleanup();
}

int TlsSocket::Write(const char *buf, uint64_t n, bool right_now) {
    if(buf == nullptr || n == 0) {
        return 0;
    }
    int wrote = 0;
    int i = 0;
    while(wrote < n) {
        i = SSL_write(m_Ssl, buf + wrote, n - wrote);
        if(i > 0) {
            wrote += i;
            if(right_now){
                return wrote;
            }
        } else {
            cout << "connection error" << endl;
            return -1;
        }
    }
    return wrote;
}

int TlsSocket::Read(char *buf, uint64_t n, bool right_now) {
    if(buf == nullptr) {
        return 0;
    }
    int read = 0;
    int i = 0;
    while(read < n) {
        i = SSL_read(m_Ssl, buf + read, n - read);
        if(i > 0) {
            read += i;
            if(right_now) {
                return read;
            }
        } else {
            cout << "connection error" << endl;
            return -1;
        }
    }
    return read;
}


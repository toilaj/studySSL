//
// Created by Joe_Jing on 2022/4/28.
//

#include "TlsServer.h"

bool TlsServer::HandShake() {
    cout << "fd = " << m_fd << endl;
    ::bind(m_fd, reinterpret_cast<sockaddr *>(&m_ServerAddress), sizeof(m_ServerAddress));
    ::listen(m_fd, 5);
    int on = 1;
    setsockopt(m_fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    m_client_fd = ::accept(m_fd, reinterpret_cast<sockaddr *>(&m_ClientAddress),
                         reinterpret_cast<socklen_t *>(&m_ClientAddress));
    if(m_client_fd <= 0) {
        cout << "accept failed:" << errno << endl;
        return false;
    }
    SSL_set_fd(m_Ssl, m_client_fd);
    int ret = SSL_accept(m_Ssl);
    if(ret != 1) {
        cout << "ssl accept failed" << endl;
        return false;
    }

    cout << "shakehand succeed" << endl;

    return true;
}

bool TlsServer::Init() {
    bool ret = TlsSocket::Init();
    m_fd = GetSocket();
    m_Ssl = GetSsl();
    return ret;
}

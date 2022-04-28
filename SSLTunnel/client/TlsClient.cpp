//
// Created by Joe_Jing on 2022/4/28.
//

#include "TlsClient.h"

bool TlsClient::HandShake() {

    if (::connect(m_fd, (struct sockaddr*) &m_ServerAddress, sizeof(m_ServerAddress)) < 0) {
        perror("Unable to connect");
        return false;
    }
    SSL_set_fd(m_Ssl, m_fd);
    if( 1 != SSL_connect(m_Ssl)) {
        perror("SSL_connect failed");
        return false;
    }
    cout << "Connected !!" << endl;

    return true;
}

bool TlsClient::Init() {
    bool ret = TlsSocket::Init();
    m_fd = GetSocket();
    m_Ssl = GetSsl();
    return ret;
}

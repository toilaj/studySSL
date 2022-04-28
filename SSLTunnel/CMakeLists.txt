cmake_minimum_required(VERSION 3.21)
project(SSLTunnel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)
set(PRO_DIR /Users/joe_jing/Documents/code/)
include_directories("${PRO_DIR}/openssl-arm/include")
add_executable(SSLTunnel_client common/TlsSocket.cpp common/TlsSocket.h client/TlsClient.cpp client/TlsClient.h client/main.cpp)
target_link_libraries(SSLTunnel_client /Users/joe_jing/Documents/code/openssl-arm/lib/libssl.a /Users/joe_jing/Documents/code/openssl-arm/lib/libcrypto.a)

add_executable(SSLTunnel_server common/TlsSocket.cpp common/TlsSocket.h server/main.cpp server/TlsServer.cpp server/TlsServer.h)
target_link_libraries(SSLTunnel_server ${PRO_DIR}/openssl-arm/lib/libssl.a ${PRO_DIR}/openssl-arm/lib/libcrypto.a)

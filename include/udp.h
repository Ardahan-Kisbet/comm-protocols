#ifndef UDP_H
#define UDP_H

// OS CHECK for SOCKET HEADERS
#ifdef _WIN32
// both WIN32 & WIN64
#define os WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#elif __linux__
// linux
#define os LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#else
#define os "unknown"

#endif

#include <string>
#include "constants.h"
#include "protocol.h"

namespace udp_client_server
{
    class UdpClient : public IProtocol
    {
    private:
        std::string m_address;
        int m_port;

    public:
        UdpClient(const std::string &address, int port) : m_address(address), m_port(port) {}
        ~UdpClient() {}
        std::string GetAddress() const;
        int GetPort() const;
        void OpenConn();
        ProtocolType GetType() override;
    };

    class UdpServer
    {
    public:
        void OpenConn();
    };
}
#endif
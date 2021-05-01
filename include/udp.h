#ifndef UDP_H
#define UDP_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
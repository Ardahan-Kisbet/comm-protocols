#include "udp.h"
#include <iostream>

namespace udp_client_server
{
    // Getter for Client Address
    std::string UdpClient::GetAddress() const
    {
        return this->m_address;
    }

    // Getter for Client Port
    int UdpClient::GetPort() const
    {
        return this->m_port;
    }

    // UDP Socket Connection
    void UdpClient::OpenConnection()
    {
        int sockfd;
        char buffer[LibConstants::BUFFER_SIZE];
    }
}
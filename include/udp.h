#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace udp_client_server
{
    class UdpClient
    {
        // create UDP socket
        // send message to server
        // wait until response from server is received

    private:
        std::string m_address;
        int m_port;

    public:
        UdpClient(const std::string &address, int port) : m_address(address), m_port(port) {}
        std::string GetAddress() const;
        int GetPort() const;
    };

    class UdpServer
    {
        // create UDP socket
        // bind the socket to server address
        // wait until DGRAM packet received from client
        // process DGRAM packet and give response to client
    };
}
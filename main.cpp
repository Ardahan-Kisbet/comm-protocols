#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "protocol.h"

#include "udp.h"

int main()
{
    std::cout << "main from client" << std::endl;
    ProtocolFactory factory(ProtocolType::Protocol_UDP);
    std::unique_ptr<IProtocol> protocol = factory.CreateProtocol();
    std::cout << std::endl
              << static_cast<int>(protocol->GetType()) << std::endl;

    udp_client_server::UdpClient udpClient("dummy address", 0);
    std::cout << "udp client constructed.." << std::endl;
    udpClient.OpenConn();

    udp_client_server::UdpServer udpServer;
    std::cout << "udp server constructed.." << std::endl;
    udpServer.OpenConn();
    std::cin.get();
}

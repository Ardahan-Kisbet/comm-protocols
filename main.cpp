#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "protocol.h"
#include "udp.h"
#include <thread>

void create_client()
{
    udp_client_server::UdpClient udpClient("127.0.0.1", 0);
    std::cout << "udp client constructed.." << std::endl;
    udpClient.OpenConn();
}

void create_server()
{
    udp_client_server::UdpServer udpServer;
    std::cout << "udp server constructed.." << std::endl;
    udpServer.OpenConn();
}

int main()
{
    std::cout << "working in main.." << std::endl;
    ProtocolFactory factory(ProtocolType::Protocol_UDP);
    std::unique_ptr<IProtocol> protocol = factory.CreateProtocol();
    std::cout << std::endl
              << static_cast<int>(protocol->GetType()) << std::endl;

    
    std::thread thread_client(create_client);
    std::thread thread_server(create_server);

    thread_client.join();
    thread_server.join();

    std::cin.get();
}

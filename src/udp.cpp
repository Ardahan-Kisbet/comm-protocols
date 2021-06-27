#include "udp.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

using SOCK_ADDR_TYPE = struct sockaddr *;

namespace udp_client_server
{
    void InitWinsock()
    {
        WSADATA wsaData;
        WORD wVersionRequested = MAKEWORD(2, 0);
        if (WSAStartup(wVersionRequested, &wsaData) != 0) {
            //LOG("WSAStartup() error");
            //return false;
            ;
        }
    }


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

    // Getter for Protocol Type
    ProtocolType UdpClient::GetType()
    {
        return ProtocolType::Protocol_UDP;
    }

    // create UDP socket (client)
    // send message to server
    // wait until response from server is received
    void UdpClient::OpenConn()
    {        
        // socket file descriptor
        char buffer[LibConstants::BUFFER_SIZE];
        struct sockaddr_in serverAddress;

        // try to create socket
        // domain   - AF_INET: IPv4
        // type     - DGRAM: UDP
        // protocol - 0: default protocol
        
        #if os == WINDOWS
        SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        #elif os == LINUX
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        #endif
        
        if (sockfd < 0)
        {
            throw "Couldn't open a socket!";
        }
        // Else: socket is created successfully.

        // zeroize server address struct
        std::memset(&serverAddress, 0, sizeof(serverAddress));

        // set server adress information
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(LibConstants::SERVER_PORT);
        serverAddress.sin_addr.s_addr = INADDR_ANY; // accept any incoming message

        #if os == WINDOWS
        InitWinsock();
        int bindResult = bind(sockfd, (sockaddr*) &serverAddress, sizeof (serverAddress));
        #endif

        while (true)
        {
            std::string msg = "Message from client..";
            #if os == WINDOWS
            sendto(sockfd, msg.c_str(), msg.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));
            #elif os == LINUX
            sendto(sockfd, msg.c_str(), msg.size(), MSG_CONFIRM, (const SOCK_ADDR_TYPE)&serverAddress, sizeof(serverAddress));
            #endif

            std::cout << "client message is sent." << std::endl;

            int received, address_len;
            #if os == WINDOWS
            received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddress, &address_len);
            #elif os == LINUX
            received = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, (SOCK_ADDR_TYPE)&serverAddress, (socklen_t *)&address_len);
            #endif


            if (received < 0)
            {
                throw "Couldn't received message!";
            }
            // Else: message is received successfully.

            // received is point to to last index
            buffer[received] = '\0';

            std::cout << "Server says: " << buffer << std::endl;
        }
        // close socket - both receiving and transmitting
        #if os == WINDOWS
        shutdown(sockfd, SD_BOTH);
        #elif os == LINUX
        shutdown(sockfd, SHUT_RDWR);
        #endif
        std::cout << "udp client closed.." << std::endl;
    }

    // create UDP socket (server)
    // bind the socket to server address
    // wait until DGRAM packet received from client
    // process DGRAM packet and give response to client
    void UdpServer::OpenConn()
    {
        // socket file descriptor
        char buffer[LibConstants::BUFFER_SIZE];
        struct sockaddr_in serverAddress, clientAddress;

        // try to create socket
        // domain   - AF_INET: IPv4
        // type     - DGRAM: UDP
        // protocol - 0: default protocol

        #if os == WINDOWS
        SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        #elif os == LINUX
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        #endif

        if (sockfd < 0)
        {
            throw "Couldn't open a socket!";
        }
        // Else: socket is created successfully.

        // zeroize server address struct
        std::memset(&serverAddress, 0, sizeof(serverAddress));
        std::memset(&clientAddress, 0, sizeof(clientAddress));

        // set server adress information
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(LibConstants::SERVER_PORT);
        serverAddress.sin_addr.s_addr = INADDR_ANY; // accept any incoming message

        // Bind the socket with the server address
        int bound;
        bound = bind(sockfd, (const SOCK_ADDR_TYPE)&serverAddress, sizeof(serverAddress));
        if (bound < 0)
        {
            throw "Couldn't bind the socket!";
        }

        int received, address_len;

        address_len = sizeof(clientAddress);
        while (true)
        {
            #if os == WINDOWS
            received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddress, &address_len);
            #elif os == LINUX
            received = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, (SOCK_ADDR_TYPE)&clientAddress, (socklen_t *)&address_len);
            #endif

            if (received < 0)
            {
                throw "Couldn't received message!";
            }
            // Else: message is received successfully.

            // received is point to to last index
            buffer[received] = '\0';

            std::cout << "Client says: " << buffer << std::endl;

            std::string msg = "Message from server..";
            #if os == WINDOWS
            sendto(sockfd, msg.c_str(), msg.size(), 0, (const SOCK_ADDR_TYPE)&clientAddress, address_len);
            #elif os == LINUX
            sendto(sockfd, msg.c_str(), msg.size(), MSG_CONFIRM, (const SOCK_ADDR_TYPE)&clientAddress, address_len);
            #endif
        }     
    }
}
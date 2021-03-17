#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "protocol.h"

int main()
{
    std::cout << "main from client" << std::endl;
    ProtocolFactory factory(ProtocolType::Protocol_UDP);
    std::unique_ptr<IProtocol> protocol = factory.CreateProtocol();
    std::cout << std::endl
              << static_cast<int>(protocol->GetType()) << std::endl;
    std::cin.get();
}

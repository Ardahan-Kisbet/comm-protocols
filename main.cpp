#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <protocol.h>
using namespace std;

int main()
{  
    std::cout<<"main"<<std::endl;
    ProtocolFactory factory(ProtocolType::Protocol_UDP);
    unique_ptr<IProtocol> protocol = factory.CreateProtocol();
    std::cout<< std::endl<<static_cast<int>(protocol->GetType()) <<std::endl;
    std::cin.get();
}

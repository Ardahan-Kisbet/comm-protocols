#include <protocol.h>

std::unique_ptr<IProtocol> ProtocolFactory::CreateProtocol(ProtocolType type)
{
	std::unique_ptr<IProtocol> temp;
	switch (type)
	{
	case ProtocolType::Protocol_HTTP:
		temp = std::make_unique<HTTP>();
		break;
	case ProtocolType::Protocol_TCP:
		temp = std::make_unique<TCP>();
		break;
	case ProtocolType::Protocol_UDP:
		temp = std::make_unique<UDP>();
		break;
	default:
		break;
	}
	return std::move(temp);
}

ProtocolType HTTP::GetType()
{
	return ProtocolType::Protocol_HTTP;
}
ProtocolType TCP::GetType()
{
	return ProtocolType::Protocol_TCP;
}
ProtocolType UDP::GetType()
{
	return ProtocolType::Protocol_UDP;
}

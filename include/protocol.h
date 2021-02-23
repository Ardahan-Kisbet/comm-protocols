#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include <memory>

enum class ProtocolType {Protocol_HTTP, Protocol_TCP, Protocol_UDP};


class IProtocol
{
public:
	//virtual void OpenConn() = 0;
	//virtual void Dispose() = 0;
	virtual ProtocolType GetType() = 0;
};

class HTTP : public IProtocol
{
public:
	HTTP() {};
	ProtocolType GetType();
};

class TCP : public IProtocol
{
public:
	TCP() {};
	ProtocolType GetType();
};

class UDP : public IProtocol
{
public:
	UDP() {};
	ProtocolType GetType();
};

class ProtocolFactory
{
private:
	std::vector<IProtocol*> m_Protocols;
public:
	ProtocolFactory() {}; // default constructor
	~ProtocolFactory() {}; // default destructor
	const IProtocol* GetProtocol() const;
	std::unique_ptr<IProtocol> CreateProtocol(ProtocolType);
};

#endif

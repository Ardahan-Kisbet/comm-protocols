#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include <memory>

enum class ProtocolType
{
	Protocol_HTTP,
	Protocol_TCP,
	Protocol_UDP
};

class IProtocol
{
public:
	//virtual void OpenConn() = 0;
	//virtual void Dispose() = 0;
	virtual ProtocolType GetType() = 0;
	IProtocol(){};
	virtual ~IProtocol(){};
};

class HTTP : public IProtocol
{
public:
	HTTP(){};
	~HTTP(){};
	ProtocolType GetType() override;
};

class TCP : public IProtocol
{
public:
	TCP(){};
	~TCP(){};
	ProtocolType GetType() override;
};

class UDP : public IProtocol
{
public:
	UDP(){};
	~UDP(){};
	ProtocolType GetType() override;
};

class ProtocolFactory
{
private:
	std::vector<IProtocol *> m_Protocols;
	ProtocolType m_type;

public:
	ProtocolFactory(ProtocolType other)
	{
		m_type = other;
	};
	~ProtocolFactory(){}; // default destructor
	const IProtocol *GetProtocol() const;
	std::unique_ptr<IProtocol> CreateProtocol();
};

#endif
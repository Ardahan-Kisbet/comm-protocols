#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include <memory>

enum class ProtocolType;

class IProtocol
{
public:
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

enum class ProtocolType
{
	Protocol_HTTP = 0,
	Protocol_TCP,
	Protocol_UDP
};

#endif
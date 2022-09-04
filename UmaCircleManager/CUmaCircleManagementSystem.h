#pragma once

#include"Common.h"

struct ServerUser
{
	SOCKET		m_Sock;
	SOCKADDR_IN m_Addr;
	std::string m_csName;
	short       m_iPort;
	void Set(SOCKET sock, SOCKADDR_IN addr)
	{
		m_Sock = sock;
		m_Addr = addr;
		m_csName = inet_ntoa(addr.sin_addr);
		m_iPort = ntohs(addr.sin_port);
	}

	bool operator==(const ServerUser& InUser) const
	{
		return m_Sock == InUser.m_Sock;
	}
};

struct ServerRunningData
{
	WSADATA Wsa;
	list<ServerUser> UserList;
};


class CUmaCircleManagementSystem
{
public:
	void Init();
	void StartServer();
	bool Run();
	void EndServer();

private:
	static bool HasClientSockError(const SOCKET& InClientSock, int InLastError);
	static bool IsClientSockValid(const SOCKET& InClientSock, int InLastError);

	void SetServerUser(const SOCKET& InClientSock, SOCKADDR_IN& InClientAddr);
	void ProcessServerUser();
	string ProcessClientCommand(const string& InClientCommand) const;

private:
	ServerRunningData ServerRunningData;
};


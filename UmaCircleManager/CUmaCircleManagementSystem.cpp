#include "CUmaCircleManagementSystem.h"
#include "CCircleMemberDatabase.h"
#include "CToolBox.h"
#include "CMainView.h"
#include "CViewManager.h"
#include "CInputManager.h"

void CUmaCircleManagementSystem::Init()
{
	CCircleMemberDatabase::Get().LoadDatas();
	CViewManager::Get().SetNextView(make_shared<CMainView>());
}

void CUmaCircleManagementSystem::StartServer()
{
	return; 

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int iRet = bind(listenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)  return;
	iRet = listen(listenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)  return;

	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);

	cout << "���� ������......." << std::endl;

	u_long isNonBlocking = 1;
	ioctlsocket(listenSock, FIONBIO, &isNonBlocking);

	while (1)	// ������ ���� �ʴ� �� ��� ���ư�.
	{
		SOCKET clientSock = accept(listenSock,
			(sockaddr*)&clientAddr, &iLen);

		const int iLastError = WSAGetLastError();
		if (HasClientSockError(clientSock, iLastError))
		{
			cout << "ErrorCode=" << clientSock << std::endl;
			continue;
		}
		if (IsClientSockValid(clientSock, iLastError))
		{
			SetServerUser(clientSock, clientAddr);
		}
		

		//recv(clientSock, szRecvBuffer, 256, 0);

		ProcessServerUser();
	}
	closesocket(listenSock);
	WSACleanup();
}

bool CUmaCircleManagementSystem::Run()
{
	try
	{
		return CViewManager::Get().UpdateView();
	}
	catch(...)
	{
		return false;
	}
	
}

void CUmaCircleManagementSystem::EndServer()
{
}

bool CUmaCircleManagementSystem::HasClientSockError(const SOCKET& InClientSock, int InLastError)
{
	if (InLastError == WSAEWOULDBLOCK)
	{
		return false;
	}
	else
	{
		return InClientSock == SOCKET_ERROR;
	}
}

bool CUmaCircleManagementSystem::IsClientSockValid(const SOCKET& InClientSock, int InLastError)
{
	return InClientSock != SOCKET_ERROR;
}

void CUmaCircleManagementSystem::SetServerUser(const SOCKET& InClientSock, SOCKADDR_IN& InClientAddr)
{
	ServerUser user;
	user.Set(InClientSock, InClientAddr);
	ServerRunningData.UserList.push_back(user);

	std::cout
		<< "ip =" << inet_ntoa(InClientAddr.sin_addr)
		<< "port =" << ntohs(InClientAddr.sin_port)
		<< "  " << std::endl;
	u_long isNonBlocking = 0;
	ioctlsocket(InClientSock, FIONBIO, &isNonBlocking);
}

void CUmaCircleManagementSystem::ProcessServerUser()
{
	auto& userList = ServerRunningData.UserList;
	for (list<ServerUser>::iterator iter = userList.begin(); iter != userList.end();)
	{
		const ServerUser& serverUser = *iter;
		char szRecvBuffer[256] = { 0 , };
		int iRecvByte = recv(serverUser.m_Sock, szRecvBuffer, 256, 0);
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				closesocket(serverUser.m_Sock);
				iter = userList.erase(iter);
				cout << serverUser.m_csName << " ���� �����." << std::endl;
				continue;
			}
			else
			{
				// Ŭ���̾�Ʈ�� �Է��� ���� �ʾ�, �ƹ��� �����͸� ���� ���� ���.
				++iter;
				continue;
			}
		}

		// �����͸� ���� ���.
		string clientCommand(szRecvBuffer);
		string processedClientCommand(ProcessClientCommand(clientCommand));

		int iSendByte = send(serverUser.m_Sock, processedClientCommand.c_str(), sizeof(processedClientCommand.c_str()), 0);
		if (iSendByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				closesocket(serverUser.m_Sock);
				iter = userList.erase(iter);
				cout << serverUser.m_csName << " ���� �����." << std::endl;
				continue;
			}
			else
			{
				// �۽Ž� ������ ������ �ƹ��� �����͸� ������ ���� ���.
				cout << "The command '" << clientCommand << "' could not be processed." << endl;
				++iter;
				continue;
			}
		}

		// �ۼ����� ���������� �̷���� ���.
		++iter;
	}
}

string CUmaCircleManagementSystem::ProcessClientCommand(const string& InClientCommand) const
{
	return string();
}

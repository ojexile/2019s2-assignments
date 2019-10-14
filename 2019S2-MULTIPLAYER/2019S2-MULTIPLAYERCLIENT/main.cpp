#include <WinSock2.h>
#include <iostream>
#include <string>

SOCKET clientsocket, serversocket;
WSADATA w;

void Init()
{
	// init sockets to be streaming tcp sockets -- can be configured to udp if the need arises
	int error = WSAStartup(0x0202, &w);

	if (error) // non-zero return means something happened.
	{
		std::cout << "!! Winsock initialisation failure." << std::endl;
		WSACleanup();
		return;
	}

	std::cout << "// Winsock initialised." << std::endl;

	// creating sockets.
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serversocket = socket(AF_INET, SOCK_STREAM, 0);
	// creating address structure for tcp socket
	sockaddr_in addr;
	addr.sin_family = AF_INET; // address family internet
	addr.sin_port = htons(23456); // assigning port 

	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 0.0.0.0 (no destination), for server mode use
												// 127.0.0.1 for 

	// binding is only needed for server
	//if (bind(serversocket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	//{
	//	std::cout << "!! error in binding\n";
	//	WSACleanup();
	//	return;
	//}

	/*if (listen(serversocket, 1) == SOCKET_ERROR)
	{
		std::cout << "!! error in listening (serversocket-side)\n";
		WSACleanup();
		return;
	}*/
	
	if (connect(serversocket, (sockaddr*)&addr,
		sizeof(addr)) == SOCKET_ERROR)
	{ // an error has occurred!
		std::cout << "!! error in connecting\n";
		WSACleanup();
		return;
	}
	
	std::cout << "// Connected!\n";

	do
	{
		char buffer[80];
		std::cout << "[] Insert message: ";
		std::cin >> buffer;

		send(serversocket, buffer, sizeof(buffer), 0);
	} while (true);


}

void Shutdown()
{
	std::cout << "// Shutting down...\n";
	shutdown(clientsocket, SD_SEND);
	closesocket(clientsocket);
	WSACleanup();
}
int main()
{
	Init();
	std::cout << "===================\n";
	Shutdown();
	return 0;
}
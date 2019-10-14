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

	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0 (no destination), for server mode use

	if (bind(serversocket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{ 
		std::cout << "!! error in binding\n";
		WSACleanup();
		return;
	}

	if (listen(serversocket, 1) == SOCKET_ERROR)
	{
		std::cout << "!! error in listening (serversocket-side)\n";
		WSACleanup();
		return;
	}

	std::cout << "// listening on given port...\n";
	int addr_size = 0;

	// initialising client socket
	clientsocket = INVALID_SOCKET;

	while (clientsocket == INVALID_SOCKET)
	{
		clientsocket = accept(serversocket, NULL, NULL);
	}
	std::cout << "// Connected!\n";
	std::cout << "// Waiting for message...\n";
	
	char buffer[80];
	int length = recv(clientsocket, buffer, sizeof(buffer), 0);

	if (length > 0)
	{
		std::cout << "[] Message Received: " << std::string(buffer).substr(0, length) << std::endl;
	}

}

void Shutdown()
{
	std::cout << "// Shutting down...\n";
	shutdown(clientsocket, SD_SEND);
	closesocket(clientsocket);
	WSACleanup();
}
void main()
{
	Init();
	std::cout << "===================\n";
	Shutdown();
}
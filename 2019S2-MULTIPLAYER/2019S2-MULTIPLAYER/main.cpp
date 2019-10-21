#include <WinSock2.h>
#include <WS2tcpip.h>
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
	// setting up socket as UDP
	serversocket = socket(AF_INET, SOCK_DGRAM, 0);
	// creating address structure for UDP/TCP server socket
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

	//if (listen(serversocket, 1) == SOCKET_ERROR)
	//{
	//	std::cout << "!! error in listening (serversocket-side)\n";
	//	WSACleanup();
	//	return;
	//}

	std::cout << "// listening on given port...\n";

	// initialising client socket
	/*clientsocket = INVALID_SOCKET;

	while (clientsocket == INVALID_SOCKET)
	{
		clientsocket = accept(serversocket, NULL, NULL);
	}*/
	std::cout << "// Connected!\n";
	std::cout << "// Waiting for message...\n";
	
	do
	{
		char buffer[80];
		int fromlen = sizeof(addr);

		//int length = recv(clientsocket, buffer, sizeof(buffer), 0);
		int length = recvfrom(serversocket, buffer, 80, 0, (sockaddr*)&addr, &fromlen);

		if (length > 0)
		{
			std::cout << "[] Message Received: " << std::string(buffer).substr(0, length) << std::endl;
			sockaddr_in* p = &addr;
			std::cout << "[>>] Sender IP : " << inet_ntop(AF_INET, &p->sin_addr, buffer, sizeof(buffer))<< " || Port:" << ntohs(addr.sin_port) << std::endl;

			//// sending message back
			//send(clientsocket, buffer, length, 0); // note that we use the length variable
		}
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
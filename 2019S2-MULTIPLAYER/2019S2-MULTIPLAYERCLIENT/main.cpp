#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <conio.h>

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
	 clientsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	 serversocket = socket(AF_INET, SOCK_DGRAM, 0);

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
	
	//if (connect(serversocket, (sockaddr*)&addr,
	//	sizeof(addr)) == SOCKET_ERROR)
	//{ // an error has occurred!
	//	std::cout << "!! error in connecting\n";
	//	WSACleanup();
	//	return;
	//}

	InetPton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	std::cout << "// Connected!\n";

	// making the socket non-blocking
	u_long nonblocking = 1;
	int m_ioctlsocket = ioctlsocket(clientsocket, FIONBIO, &nonblocking);

	char exitcode = ':';
	do
	{
		char buffer[80];
		//std::cout << "[] Insert message: ";
		//std::cin >> buffer;

		if (_kbhit())
		{
			std::string inputstring;
			std::getline(std::cin, inputstring);
			int length = sendto(serversocket, inputstring.c_str(), (int)inputstring.length() + 1, 0, (sockaddr*)&addr, sizeof(addr));

			buffer[0] = inputstring[0];
		}

		if (buffer[0] == exitcode)
			break;

		//int length = sendto(serversocket, buffer, strlen(buffer), 0, (sockaddr*)&addr, sizeof(addr));
		//send(serversocket, buffer, sizeof(buffer), 0);


		/*char buffer2[80];

		int length = recv(serversocket, buffer2, sizeof(buffer2), 0);

		if (length > 0)
		{
			std::cout << "[] Message Received From Server: " << std::string(buffer2).substr(0, length) << std::endl;
		}*/
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
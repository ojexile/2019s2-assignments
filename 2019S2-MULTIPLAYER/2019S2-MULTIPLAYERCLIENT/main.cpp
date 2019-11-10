#include <WinSock2.h>
#include <iostream>
#include <string>
#include <conio.h>

SOCKET serversocket;
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
	serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// creating address structure for tcp socket
	sockaddr_in addr;
	addr.sin_family = AF_INET; // address family internet
	addr.sin_port = htons(23456); // assigning port 
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 0.0.0.0 (no destination), for server mode use
													// 127.0.0.1 for smth else... cant remember.

	// ioctlsocket
	u_long somelong = 1;
	int ioctl = ioctlsocket(serversocket, FIONBIO, &somelong);

	// do not check == SOCKET_ERROR here because Async mode will always return SOCKET_ERROR
	connect(serversocket, (sockaddr*)&addr, sizeof(addr));
	
	std::cout << "// Connected!\n";
	std::cout << "[] Insert message: ";

	char exitcode = ':';
	do
	{
		char exitcodecheck = '?';
		if (_kbhit())
		{
			std::string input;
			std::getline(std::cin, input);

			send(serversocket, input.c_str(), (int)input.length() + 1, 0);
			exitcodecheck = input[0];

		}

		if (exitcodecheck == exitcode)
			break;

		// FDSET STUFF
		fd_set fset;
		FD_ZERO(&fset);
		FD_SET(serversocket, &fset);

		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 10000;

		if (select(0, &fset, 0, 0, &tval) > 0)
		{
			// stuff is done ehre 
			char buffer2[80];

			int length = recv(serversocket, buffer2, sizeof(buffer2), 0);

			if (length > 0)
			{
				std::cout << "[] Message Received From Server: " << std::string(buffer2).substr(0, length) << std::endl;
				std::cout << "[] Insert message: ";
			}
			else if (length == SOCKET_ERROR)
			{
				std::cout << "[] Server went offline" << std::endl;
				break;
			}
		}
		/*if (FD_ISSET(serversocket, &fset))
		{	

		}*/
	} while (true);


}

void Shutdown()
{
	std::cout << "// Shutting down...\n";
	shutdown(serversocket, SD_SEND);
	closesocket(serversocket);
	WSACleanup();
}
int main()
{
	Init();
	std::cout << "===================\n";
	Shutdown();
	return 0;
}
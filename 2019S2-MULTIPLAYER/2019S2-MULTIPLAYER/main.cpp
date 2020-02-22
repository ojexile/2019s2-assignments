#include <WinSock2.h>
#include <iostream>
#include <string>
#include <vector> 
#include "User.h"
#pragma comment(lib, "Ws2_32.lib")

SOCKET clientsocket, serversocket;
WSADATA w;
std::vector<user*> socks;
	
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
	//clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	//// initialising client socket
	//clientsocket = INVALID_SOCKET;

	//while (clientsocket == INVALID_SOCKET)
	//{
	//	clientsocket = accept(serversocket, NULL, NULL);
	//}
	//std::cout << "// Connected!\n";
	//std::cout << "// Waiting for message...\n";
	

	do
	{

		fd_set fset;
		FD_ZERO(&fset);
		FD_SET(serversocket, &fset);

		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 10000;

		u_long somelong;

		for (std::vector<user*>::iterator itr = socks.begin(); itr != socks.end(); ++itr)
		{
			FD_SET((*itr)->s, &fset);
		}

		if (select(0, &fset, 0, 0, &tval) > 0)
		{
			// check if main socket is FD_ISSET()
			if (FD_ISSET(serversocket, &fset))
			{
				//creates new socket for new connection
				SOCKET tmpsocket = accept(serversocket, NULL, NULL);
				// sets to non-blocking
				ioctlsocket(tmpsocket, FIONBIO, &somelong);
				// insert into an array
				user* tmpuser = new user(tmpsocket);
				socks.push_back(tmpuser);

				std::cout << ">> New Connection detected" << std::endl;
				send(tmpsocket, "Enter username: ", 17, 0);
			}

			char buffer[255];
			for (std::vector<user*>::iterator itr = socks.begin(); itr != socks.end(); ++itr)
			{
				if (FD_ISSET((*itr)->s, &fset))
				{
					int length = recv((*itr)->s, buffer, sizeof(buffer), 0);
					if (length == SOCKET_ERROR) // client has probably disconnected
					{
						std::cout << "Client (" << (int)(*itr)->s << ") has disconnected." << std::endl;
						socks.erase(itr);
						break;
					}

					// BUFFER PROCESSING
					else if (length > 0) 
					{
						if ((*itr)->afk) // if its afk and seds a message, take it out of afk
						{
							(*itr)->afk = false;
							std::cout << (*itr)->name << " has returned from AFK." << std::endl; ;
						}

						// if username isnt set, take opportunity to set the name with the data sent from its 1st packet
						if ((*itr)->name == "NEWUSER")
						{
							(*itr)->name = std::string(buffer);
							std::string tmpstr = "Your username is now: " + (*itr)->name;
							// send to the maker
							send((*itr)->s, tmpstr.c_str(), tmpstr.length(), 0);

							//send it to everyone
							tmpstr = "[Server]A new user (" + (*itr)->name + ") has connected!";
							for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
							{
								if (/*(*itr)->name != (*itr2)->name && */(*itr2)->name != "NEWUSER")
									send((*itr2)->s, tmpstr.c_str(), tmpstr.length(), 0);
							}
							std::cout << tmpstr << std::endl;
						}
						else if (strncmp(buffer, "/list", 5) == 0) // list
						{
							//List out users
							
							std::string tmpstr = "==========\n[Server]List of users:";
							for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
							{
								if ((*itr2)->name != "NEWUSER")
									tmpstr += "\n"+ (*itr2)->name;
								if ((*itr2)->afk)
									tmpstr += "(AFK)";
							}
							tmpstr += "\n==========";
							send((*itr)->s, tmpstr.c_str(), tmpstr.length(), 0);
						}
						else if (strncmp(buffer, "/afk", 4) == 0) //afk
						{
							(*itr)->afk = true;
							std::cout << (*itr)->name << " has gone AFK." << std::endl;
						}
						else if (strncmp(buffer, "/w", 2) == 0) //whisper
						{
							std::string wname = std::string(buffer).substr(3, length);
							std::string msg;
							int pos = wname.find(" ");
							msg = wname.substr(pos + 1, length);
							wname = wname.substr(0, pos);
							std::string tmpstr = "(W)[" + (*itr)->name + "]" + msg;
							for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
							{
								if (wname == (*itr2)->name)
								{
									send((*itr2)->s, tmpstr.c_str(), tmpstr.length(), 0);
									std::cout << (*itr)->name << " whispered to " << (*itr2)->name << ": " << msg << std::endl;
								}
							}
						}
						else // default message sending 
						{
							std::string tmpstr = "[" + (*itr)->name + "]: " + std::string(buffer);
							std::cout << '[' << (*itr)->name << ']' << std::string(buffer).substr(0, length) << std::endl;
							for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
							{
								if ((*itr)->name != (*itr2)->name && (*itr2)->name != "New User")
									send((*itr2)->s, tmpstr.c_str(), tmpstr.length(), 0);
							}
						}
					}

				}
			}
		}
		//char buffer[80];
		//int length = recv(clientsocket, buffer, sizeof(buffer), 0);

		//if (length > 0)
		//{

		//	std::cout << "[] Message Received: " << std::string(buffer).substr(0, length) << std::endl;

		//	// sending message back
		//	send(clientsocket, buffer, length, 0); // note that we use the length variable
		//}
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
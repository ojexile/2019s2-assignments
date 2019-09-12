//Multithreaded socket Server

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 8192
#define DEFAULT_PORT 7890
#define MAX_SESSION_LIMIT 100

struct SessionInfo
{
	SOCKET Socket; //Socket handle
	char IPAddress[16]; //Ip address: xxx.xxx.xxx.xxx
	char MessageBuffer[DEFAULT_BUFLEN]; //Message buffer
	int MessageSize; //message size in buffer
	HANDLE hThread;
	DWORD dwThreadID;
	CRITICAL_SECTION cs_SessionList;
	string Nickname;
	string channel;

} g_SessionList[MAX_SESSION_LIMIT];

struct Channel
{
	string name;
	string password;
	SOCKET adminSOCKET = 0;
};
vector<Channel *> channelList;

string packetDecoder(string, int packetLength);
string packetEncoder(string, int packetLength);
int add_new_session(SOCKET NewSocket);
void close_session(int SessionIndex);
DWORD WINAPI RecvThread(void *arg);

int main()
{
	WSADATA wsaData; //Declare some variables
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	sockaddr_in ServerAddress;
	sockaddr_in ClientAddress;
	int ClientAddressLen;
	int Result = 0;
	int SessionIndex;

	//Create the default channel
	Channel* ch = new Channel;
	channelList.push_back(ch);
	ch->name = "general";
	ch->password = "";

	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = 0;
	GetConsoleMode(hConsole, &prevMode);
	SetConsoleMode(hConsole, prevMode & ~ENABLE_QUICK_EDIT_MODE);

	//Init session structure array
	for (int i = 0; i < MAX_SESSION_LIMIT; ++i)
	{
		memset(&g_SessionList[i], '\0', sizeof(struct SessionInfo));
	}

	//Init winsock
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (NO_ERROR != Result)
	{
		printf("Error at WSAStartup()\n");
		return 1;
	}
	else
	{
		printf("WSAStartup success.\n");
	}

	//Create a socket for listening for incoming connetion requests
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ListenSocket)
	{
		printf("socket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	else
	{
		printf("socket creation success\n");
	}

	//The sockaddr_in structure specifies the address family, 
	//Ip address, and port for the socket that is being bound
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(DEFAULT_PORT);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//Bind the socket
	Result = bind(ListenSocket, (SOCKADDR *)&ServerAddress, sizeof(ServerAddress));
	if (SOCKET_ERROR == Result)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("bind returned success\n");
	}

	//Listen for incoming connection requests on the created socket
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN))
	{
		printf("liten function failed with error: %d\n", WSAGetLastError());
	}
	printf("Listening on socket...\n");

	//Main loop
	do
	{
		//Create a SOCKET for accepting incoming requests.
		printf("Waiting for client to connect...\n");

		//Accept the connection
		ClientAddressLen = sizeof(ClientAddress);
		ClientSocket = accept(ListenSocket, (struct sockaddr*)&ClientAddress, &ClientAddressLen);
		if (INVALID_SOCKET == ClientSocket)
		{
			printf("accepted failed with error: %d", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		SessionIndex = add_new_session(ClientSocket);
		printf("Client connected. IP Address: %d.%d.%d.%d, Port Number:%d, SessionIndex:%d\n",
			(ClientAddress.sin_addr.S_un.S_un_b.s_b1),
			(ClientAddress.sin_addr.S_un.S_un_b.s_b2),
			(ClientAddress.sin_addr.S_un.S_un_b.s_b3),
			(ClientAddress.sin_addr.S_un.S_un_b.s_b4),
			ntohs(ClientAddress.sin_port),
			SessionIndex);

		//Create thread for new connected session
		g_SessionList[SessionIndex].hThread = CreateThread(NULL, 0,
			RecvThread, //Thread function
			(LPVOID)SessionIndex, //Passing argument
			0, &g_SessionList[SessionIndex].dwThreadID);

	} while (1);

	//Close existing socket
	closesocket(ListenSocket);

	//terminate use of winsock 2 dll(Ws2_32.dll_
	WSACleanup();

	return 0;
}

int add_new_session(SOCKET NewSocket)
{
	int SessionIndex;

	for (SessionIndex = 0; SessionIndex < MAX_SESSION_LIMIT; SessionIndex++)
	{
		//find empty slot
		if (0 == g_SessionList[SessionIndex].Socket)
		{
			//initialize critical section
			InitializeCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
			EnterCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
			g_SessionList[SessionIndex].Socket = NewSocket;
			g_SessionList[SessionIndex].MessageSize = 0;
			LeaveCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
			//More info for session

			return SessionIndex;
		}
	}

	return -1; //session list full
}

void close_session(int SessionIndex)
{
	/// Closes an existing socket
	closesocket(g_SessionList[SessionIndex].Socket);
	// Delete critical Section
	DeleteCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
	printf("Connection Closed. SessionIndex:%d, hThread:%d, ThreadID:%d\n",
		SessionIndex, (int)g_SessionList[SessionIndex].hThread,
		g_SessionList[SessionIndex].dwThreadID);
	/// Reset the structure data.
	memset(&g_SessionList[SessionIndex], '\0', sizeof(struct SessionInfo));
}

DWORD WINAPI RecvThread(void *arg)
{
	char RecvBuffer[DEFAULT_BUFLEN];
	int RecvResult;
	int SessionIndex;
	SessionIndex = (int)arg;
	printf("New thread created for SessionIndex:%d, hThread:%d, ThreadID:%d\n",
		SessionIndex, (int)g_SessionList[SessionIndex].hThread,
		g_SessionList[SessionIndex].dwThreadID);
	while (1) {
		///----------------------
		/// Receive and echo the message until the peer closes the connection
		memset(g_SessionList[SessionIndex].MessageBuffer, '\0', DEFAULT_BUFLEN);
		RecvResult = recv(g_SessionList[SessionIndex].Socket,
			RecvBuffer, DEFAULT_BUFLEN, 0);
		if (0 < RecvResult)
		{
			// Copy the RecvBuffer into Session Buffer
			EnterCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
			memcpy(&g_SessionList[SessionIndex].MessageBuffer[0],
				&RecvBuffer, RecvResult);
			g_SessionList[SessionIndex].MessageSize = RecvResult;
			LeaveCriticalSection(&g_SessionList[SessionIndex].cs_SessionList);
			printf("Received from SessionIndex:%d, hThread:%d, ThreadID:%d\n",
				SessionIndex, (int)g_SessionList[SessionIndex].hThread,
				g_SessionList[SessionIndex].dwThreadID);
			printf("Bytes received : %d\n", g_SessionList[SessionIndex].MessageSize);
			printf("Encoded Buffer received : %s\n", g_SessionList[SessionIndex].MessageBuffer);
			
			string RecvMessage = packetDecoder(string(g_SessionList[SessionIndex].MessageBuffer), strlen(g_SessionList[SessionIndex].MessageBuffer));

			if (g_SessionList[SessionIndex].Nickname != "")
			{
				cout << "<MESSAGE>" << g_SessionList[SessionIndex].Nickname << ": " << RecvMessage << endl;
			}
			else
			{
				cout << "<MESSAGE>" << g_SessionList[SessionIndex].Socket << ": " << RecvMessage << endl;
			}
			
			//Commands
			if (RecvMessage[0] == '/')
			{
				istringstream ss(RecvMessage);
				string command;
				string text;
				std::getline(ss, command, '/');
				std::getline(ss, command, ' ');

				if (command == "nickname")
				{
					//New user joined the server
					if (g_SessionList[SessionIndex].Nickname == "")
					{
						std::getline(ss, text, ' ');
						g_SessionList[SessionIndex].Nickname = string(text);
						g_SessionList[SessionIndex].channel = string("general");

						//Welcome message for new user
						string WelcomeMsg = "Welcome to my Multithreaded server! Your nickname is " + g_SessionList[SessionIndex].Nickname + "\n";
						WelcomeMsg += "Type /help for a list of commands!\n";
						//Info msg to new client
						string InfoMsg = "Currently online users: ";
						bool firstID = true;
						for (int i = 0; i < MAX_SESSION_LIMIT; i++)
						{
							if (g_SessionList[i].Socket != 0 && i != SessionIndex)
							{
								if (firstID == true)
								{
									InfoMsg += "<" + g_SessionList[i].channel + ">" + g_SessionList[i].Nickname;
									firstID = false;
								}
								else
								{
									InfoMsg += ", <" + g_SessionList[i].channel + ">" + g_SessionList[i].Nickname;
								}
							}
						}

						//If no users yet
						if (InfoMsg == "Currently online users: " || channelList[0]->adminSOCKET == 0)
						{
							InfoMsg += "None\nYou are now the admin of this channel";
							channelList[0]->adminSOCKET = g_SessionList[SessionIndex].Socket;
						}
							
						//Send as 1 message
						WelcomeMsg += InfoMsg;

						//Encode and send
						WelcomeMsg = packetEncoder(WelcomeMsg, WelcomeMsg.length());
						send(g_SessionList[SessionIndex].Socket, WelcomeMsg.c_str(), WelcomeMsg.length() + 1, 0);

						//Notice msg to all other clients
						for (int i = 0; i < MAX_SESSION_LIMIT; i++)
						{
							if (g_SessionList[i].Socket != 0 && i != SessionIndex)
							{
								string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has joined the server";
								NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
								send(g_SessionList[i].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
							}
						}
					}
					else
					{
						std::getline(ss, text, ' ');

						//Notify other users that nickname changed
						for (int i = 0; i < MAX_SESSION_LIMIT; i++)
						{
							if (g_SessionList[i].Socket != 0 && i != SessionIndex)
							{
								string message = g_SessionList[SessionIndex].Nickname + " has changed nickname to " + text;
								message = packetEncoder(message, message.length());
								send(g_SessionList[i].Socket, message.c_str(), message.length(), 0);
							}
						}

						g_SessionList[SessionIndex].Nickname = text;

						//notify user that nickname has been changed
						string message = "Your nickname has been changed to " + text;
						message = packetEncoder(message, message.length());
						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}					
				}
				else if (command == "list")
				{
					string message = "Currently online users: ";
					bool firstID = true;
					for (int i = 0; i < MAX_SESSION_LIMIT; i++)
					{
						if (g_SessionList[i].Socket != 0)
						{
							if (firstID == true)
							{
								message += "<" + g_SessionList[i].channel + ">";
								for (unsigned int j = 0; j < channelList.size(); ++j)
								{
									if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
									{
										message += "<ADMIN>";
										break;
									}
								}
								message += g_SessionList[i].Nickname;
								firstID = false;
							}
							else
							{
								message += ", <" + g_SessionList[i].channel + ">";
								for (unsigned int j = 0; j < channelList.size(); ++j)
								{
									if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
									{
										message += "<ADMIN>";
										break;
									}
								}
								message += g_SessionList[i].Nickname;
							}
						}
					}

					if (message == "Currently online users: ")
						message += "None";

					//encode and send
					message = packetEncoder(message, message.length());
					send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
				}
				else if (command == "whisper")
				{
					string targetName; 
					std::getline(ss, targetName, ' ');
					string RecvMessage2;
					std::getline(ss, RecvMessage2);
					bool targetFound = false;

					//search for target user and send whisper to target user and a copy to sender
					for (int i = 0; i < MAX_SESSION_LIMIT; i++)
					{
						if (g_SessionList[i].Nickname == targetName)
						{
							//construct, encode message and send
							string message = "<Whisper><" + g_SessionList[SessionIndex].channel + ">" + g_SessionList[SessionIndex].Nickname + ": " + RecvMessage2;
							message = packetEncoder(message, message.length());

							send(g_SessionList[i].Socket, message.c_str(), message.length(), 0);
							//send a copy to sender
							send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
							targetFound = true;
						}
					}

					//if target not found, send error to sender
					if (targetFound == false)
					{
						//construct, encode message and send
						string message = "<Whisper>User not found";
						message = packetEncoder(message, message.length());

						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}
				}
				else if (command == "help")
				{
					string message;
					message += "\nCOMMAND LIST\n";
					message += "/help \t\t\t\t\t(Show list of commands)\n";
					message += "/nickname <newNickname> \t\t(Change current nickname)\n";
					message += "/list \t\t\t\t\t(Show list of current users in the server)\n";	
					message += "/broadcast <message> \t\t\t(Broadcast message through entire server)\n";
					message += "/whisper <targetuser> <message> \t(Direct message a user regardless of channel)\n";
					message += "/quit \t\t\t\t\t(Quit the server)\n";
					message += "/create <channelName> <password> \t(Create a new channel, can leave password empty if no password)\n";
					message += "/join <channelName> <password> \t\t(Join another channel, can leave password empty if no password)\n";
					message += "/setpassword <newpassword> \t\t(Change channel password if user is admin)\n";
					message += "/channelname <newchannelName> \t\t(Change channel name if user is admin)\n";
					//encode and send
					message = packetEncoder(message, message.length());
					send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
				}
				else if (command == "broadcast")
				{
					std::getline(ss, text);

					//If text isnt empty
					if (text != "")
					{
						for (int i = 0; i < MAX_SESSION_LIMIT; ++i)
						{
							if (g_SessionList[i].Socket != 0)
							{
								//construct, encode message and send
								string message = "<Broadcast><" + g_SessionList[SessionIndex].channel + ">" + g_SessionList[SessionIndex].Nickname + ": " + text;
								message = packetEncoder(message, message.length());

								send(g_SessionList[i].Socket, message.c_str(), message.length(), 0);
							}							
						}
					}
					else
					{
						//construct, encode message and send
						string message = "<Broadcast>You didnt enter anything!";
						message = packetEncoder(message, message.length());

						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}
				}
				else if (command == "quit")
				{
					//Tell other users in server that user left
					for (int i = 0; i < MAX_SESSION_LIMIT; i++)
					{
						if (g_SessionList[i].Socket != 0 && i != SessionIndex)
						{
							string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has left the server";
							NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
							send(g_SessionList[i].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
						}
					}

					//Check if user is Admin of the channel
					for (unsigned int j = 0; j < channelList.size(); ++j)
					{
						//If user is admin, move it to another user
						if (g_SessionList[SessionIndex].Socket == channelList[j]->adminSOCKET)
						{
							bool newAdminSet = false;
							for (int k = 0; k < MAX_SESSION_LIMIT; ++k)
							{
								if (g_SessionList[k].Socket != 0 && k != SessionIndex && g_SessionList[k].channel == g_SessionList[SessionIndex].channel)
								{
									channelList[j]->adminSOCKET = g_SessionList[k].Socket;
									newAdminSet = true;
									//Send message to new admin telling user that he/she is new admin
									string NoticeMsg = "You are now the admin of this channel";
									NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
									send(g_SessionList[k].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
								}
							}

							//if no one in channel and channel is not 'general', delete the channel
							if (newAdminSet == false && g_SessionList[SessionIndex].channel != "general")
							{
								for (unsigned int j = 0; j < channelList.size(); ++j)
								{
									if (channelList[j]->name == g_SessionList[SessionIndex].channel)
									{
										channelList.erase(channelList.begin() + j);
									}
								}
							}
							else if (newAdminSet == false && g_SessionList[SessionIndex].channel == "general")
							{
								channelList[0]->adminSOCKET = 0;
							}
						}
					}

					//construct, encode message and send
					string message = "/ClientQuit";
					message = packetEncoder(message, message.length());
					send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);					
				}
				else if (command == "create")
				{
					string channelName;
					std::getline(ss, channelName, ' ');
					bool targetFound = false;

					//search if channel already exists
					for (unsigned int i = 0; i < channelList.size(); ++i)
					{
						if (channelName == channelList[i]->name)
							targetFound = true;
					}

					//if channel already exists, send error to sender
					if (targetFound == true)
					{
						//construct, encode message and send
						string message = "<Create>Channel already exists";
						message = packetEncoder(message, message.length());

						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}
					//else create the channel
					else
					{
						//Tell other users in previous channel that user left
						for (int i = 0; i < MAX_SESSION_LIMIT; i++)
						{
							if (g_SessionList[i].Socket != 0 && g_SessionList[i].channel == g_SessionList[SessionIndex].channel && i != SessionIndex)
							{
								string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has left the channel";
								NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
								send(g_SessionList[i].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
							}
						}

						//Check if user is Admin of the previous channel
						for (unsigned int j = 0; j < channelList.size(); ++j)
						{
							//If user is admin, move it to another user
							if (g_SessionList[SessionIndex].Socket == channelList[j]->adminSOCKET)
							{
								bool newAdminSet = false;
								for (int k = 0; k < MAX_SESSION_LIMIT; ++k)
								{
									if (g_SessionList[k].Socket != 0 && k != SessionIndex && g_SessionList[k].channel == g_SessionList[SessionIndex].channel)
									{
										channelList[j]->adminSOCKET = g_SessionList[k].Socket;
										newAdminSet = true;
										//Send message to new admin telling user that he/she is new admin
										string NoticeMsg = "You are now the admin of this channel";
										NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
										send(g_SessionList[k].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
										break;
									}
								}

								//if no one in channel and channel is not 'general', delete the channel
								if (newAdminSet == false && g_SessionList[SessionIndex].channel != "general")
								{
									for (unsigned int j = 0; j < channelList.size(); ++j)
									{
										if (channelList[j]->name == g_SessionList[SessionIndex].channel)
										{
											channelList.erase(channelList.begin() + j);
										}
									}
								}
								//if channel is 'general' and no one in channel
								else if (newAdminSet == false && g_SessionList[SessionIndex].channel == "general")
								{
									channelList[0]->adminSOCKET = 0;
								}
							}
						}					

						string channelPassword;
						std::getline(ss, channelPassword, ' ');

						Channel* ch = new Channel;
						channelList.push_back(ch);
						ch->name = channelName;
						ch->password = channelPassword;
						ch->adminSOCKET = g_SessionList[SessionIndex].Socket;
						g_SessionList[SessionIndex].channel = ch->name;

						//construct, encode message and send
						string message = "<Create>" + channelName + " channel created and joined\nYou are now the admin of this channel";
						message = packetEncoder(message, message.length());

						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}
				}
				else if (command == "join")
				{
					string channelName;
					std::getline(ss, channelName, ' ');
					bool targetFound = false;

					//search if channel already exists
					for (unsigned int i = 0; i < channelList.size(); ++i)
					{
						if (channelName == channelList[i]->name)
						{
							targetFound = true;
							//check if there is a password
							if (channelList[i]->password != "")
							{							
								string channelPassword;
								std::getline(ss, channelPassword, ' ');

								//if password correct
								if (channelList[i]->password == channelPassword)
								{
									//Tell other users in previous channel that user left
									for (int j = 0; j < MAX_SESSION_LIMIT; j++)
									{
										if (g_SessionList[j].Socket != 0 && g_SessionList[j].channel == g_SessionList[SessionIndex].channel && j != SessionIndex)
										{
											string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has left the channel";
											NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
											send(g_SessionList[j].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
										}
									}
									
									//Check if user is Admin of the channel
									for (unsigned int j = 0; j < channelList.size(); ++j)
									{
										//If user is admin, move it to another user
										if (g_SessionList[SessionIndex].Socket == channelList[j]->adminSOCKET)
										{
											bool newAdminSet = false;
											for (int k = 0; k < MAX_SESSION_LIMIT; ++k)
											{
												if (g_SessionList[k].Socket != 0 && k != SessionIndex && g_SessionList[k].channel == g_SessionList[SessionIndex].channel)
												{
													channelList[j]->adminSOCKET = g_SessionList[k].Socket;
													newAdminSet = true;
													//Send message to new admin telling user that he/she is new admin
													string NoticeMsg = "You are now the admin of this channel";
													NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
													send(g_SessionList[k].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
												}
											}

											//if no one in channel and channel is not 'general', delete the channel
											if (newAdminSet == false && g_SessionList[SessionIndex].channel != "general")
											{
												for (unsigned int j = 0; j < channelList.size(); ++j)
												{
													if (channelList[j]->name == g_SessionList[SessionIndex].channel)
													{
														channelList.erase(channelList.begin() + j);
													}
												}
											}
											else if (newAdminSet == false && g_SessionList[SessionIndex].channel == "general")
											{
												channelList[0]->adminSOCKET = 0;
											}
										}
									}																		

									g_SessionList[SessionIndex].channel = channelList[i]->name;

									//construct, encode message and send
									string message = "<Join>Joined " + channelName + " channel\n";
									message += "Users currently in " + channelName + " channel: ";
									bool firstID = true;
									for (int i = 0; i < MAX_SESSION_LIMIT; i++)
									{
										if (g_SessionList[i].channel == channelName)
										{
											if (firstID == true)
											{
												for (unsigned int j = 0; j < channelList.size(); ++j)
												{
													if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
													{
														message += "<ADMIN>";
														break;
													}
												}
												message += g_SessionList[i].Nickname;
												firstID = false;
											}
											else
											{
												message += ", ";
												for (unsigned int j = 0; j < channelList.size(); ++j)
												{
													if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
													{
														message += "<ADMIN>";
														break;
													}
												}
												message += g_SessionList[i].Nickname;
											}
										}
									}

									message = packetEncoder(message, message.length());

									send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);

									//Tell other users in the channel that user joined
									for (int j = 0; j < MAX_SESSION_LIMIT; j++)
									{
										if (g_SessionList[j].Socket != 0 && g_SessionList[j].channel == g_SessionList[SessionIndex].channel && j != SessionIndex)
										{
											string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has joined the channel";
											NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
											send(g_SessionList[j].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
										}
									}
								}
								else
								{
									//construct, encode message and send
									string message = "<Join>Wrong password";
									message = packetEncoder(message, message.length());

									send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
								}
							}
							//If no password
							else
							{
								//Tell other users in previous channel that user left
								for (int j = 0; j < MAX_SESSION_LIMIT; j++)
								{
									if (g_SessionList[j].Socket != 0 && g_SessionList[j].channel == g_SessionList[SessionIndex].channel && j != SessionIndex)
									{
										string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has left the channel";
										NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
										send(g_SessionList[j].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
									}
								}
							
								//Check if user is Admin of the channel
								for (unsigned int j = 0; j < channelList.size(); ++j)
								{
									//If user is admin, move it to another user
									if (g_SessionList[SessionIndex].Socket == channelList[j]->adminSOCKET)
									{
										bool newAdminSet = false;
										for (int k = 0; k < MAX_SESSION_LIMIT; ++k)
										{
											if (g_SessionList[k].Socket != 0 && k != SessionIndex && g_SessionList[k].channel == g_SessionList[SessionIndex].channel)
											{
												channelList[j]->adminSOCKET = g_SessionList[k].Socket;
												newAdminSet = true;
												//Send message to new admin telling user that he/she is new admin
												string NoticeMsg = "You are now the admin of this channel";
												NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
												send(g_SessionList[k].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
											}
										}

										//if no one in channel and channel is not 'general', delete the channel
										if (newAdminSet == false && g_SessionList[SessionIndex].channel != "general")
										{
											for (unsigned int j = 0; j < channelList.size(); ++j)
											{
												if (channelList[j]->name == g_SessionList[SessionIndex].channel)
												{
													channelList.erase(channelList.begin() + j);
												}
											}
										}
										else if (newAdminSet == false && g_SessionList[SessionIndex].channel == "general")
										{
											channelList[0]->adminSOCKET = 0;
										}
									}
								}															

								g_SessionList[SessionIndex].channel = channelList[i]->name;								

								//construct, encode message and send
								string message = "<Join>Joined " + channelName + " channel\n";
								message += "Users currently in " + channelName + " channel: ";
								bool firstID = true;
								for (int i = 0; i < MAX_SESSION_LIMIT; i++)
								{
									if (g_SessionList[i].channel == channelName)
									{
										if (firstID == true)
										{
											for (unsigned int j = 0; j < channelList.size(); ++j)
											{
												if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
												{
													message += "<ADMIN>";
													break;
												}
											}
											message += g_SessionList[i].Nickname;
											firstID = false;
										}
										else
										{
											message += ", ";
											for (unsigned int j = 0; j < channelList.size(); ++j)
											{
												if (channelList[j]->adminSOCKET == g_SessionList[i].Socket)
												{
													message += "<ADMIN>";
													break;
												}
											}
											message += g_SessionList[i].Nickname;
										}
									}
								}

								//check if user joined general channel & if admin exists in general channel
								if (channelList[i]->name == "general" && channelList[i]->adminSOCKET == 0)
								{
									channelList[i]->adminSOCKET = g_SessionList[SessionIndex].Socket;
									message += "\nYou are now the admin of this channel";
								}

								message = packetEncoder(message, message.length());
								send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);

								//Tell other users in the channel that user joined
								for (int j = 0; j < MAX_SESSION_LIMIT; j++)
								{
									if (g_SessionList[j].Socket != 0 && g_SessionList[j].channel == g_SessionList[SessionIndex].channel && j != SessionIndex)
									{
										string NoticeMsg = g_SessionList[SessionIndex].Nickname + " has joined the channel";
										NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
										send(g_SessionList[j].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
									}
								}
							}							
						}
					}

					//if channel doesnt exist, send error to sender
					if (targetFound == false)
					{
						//construct, encode message and send
						string message = "<Join>Channel doesnt exist";
						message = packetEncoder(message, message.length());

						send(g_SessionList[SessionIndex].Socket, message.c_str(), message.length(), 0);
					}
				}
				else if (command == "setpassword")
				{
					bool channelPasswordSwitched = false;
					for (unsigned int i = 0; i < channelList.size(); ++i)
					{
						if (channelList[i]->adminSOCKET == g_SessionList[SessionIndex].Socket)
						{
							std::getline(ss, text, ' ');
							channelList[i]->password = text;

							//tell user that password has been changed
							string NoticeMsg = channelList[i]->name + " channel password has been changed to " + text;
							NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
							send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
							channelPasswordSwitched = true;
							break;					
						}
					}

					//User doesn't have permissions to switch
					if (channelPasswordSwitched == false)
					{
						string NoticeMsg = "You are not admin of this channel!";
						NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
						send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
					}
				}
				else if (command == "channelname")
				{
					bool channelNameSwitched = false;
					for (unsigned int i = 0; i < channelList.size(); ++i)
					{
						if (channelList[i]->adminSOCKET == g_SessionList[SessionIndex].Socket)
						{
							std::getline(ss, text, ' ');
							
							if (channelList[i]->name != "general")
							{
								//tell user that channel name has been changed
								string NoticeMsg = channelList[i]->name + " channel name has been changed to " + text;
								NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
								send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);

								channelList[i]->name = text;

								string oldChannelName = g_SessionList[SessionIndex].channel;
								//change sessioninfo of users in that channel
								for (int j = 0; j < MAX_SESSION_LIMIT; ++j)
								{
									if (g_SessionList[j].channel == oldChannelName)
									{
										g_SessionList[j].channel = text;
									}
								}
							}
							else
							{
								//general server cant change name as it is default
								string NoticeMsg = "You can't change the name of general channel";
								NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
								send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);								
							}
							channelNameSwitched = true;
							break;
						}
					}

					//User doesn't have permissions to switch
					if (channelNameSwitched == false)
					{
						string NoticeMsg = "You are not admin of this channel!";
						NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
						send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
					}
				}
				else
				{
					string NoticeMsg = "No such command, type /help for a list of available commands.";
					NoticeMsg = packetEncoder(NoticeMsg, NoticeMsg.length());
					send(g_SessionList[SessionIndex].Socket, NoticeMsg.c_str(), NoticeMsg.length() + 1, 0);
				}
			}

			//Normal message
			else
			{
				//Construct the message and Encode it
				string message = "";
				message += g_SessionList[SessionIndex].Nickname + ": " + RecvMessage;
				message = packetEncoder(message, message.length());

				//send to everyone in same channel by default
				for (int i = 0; i < MAX_SESSION_LIMIT; ++i)
				{
					if (g_SessionList[i].Socket != 0 && g_SessionList[i].channel == g_SessionList[SessionIndex].channel)
					{
						RecvResult = send(g_SessionList[i].Socket,	message.c_str(), message.length() + 1, 0);
					}
				}
			}
		}
		else if (0 == RecvResult)
		{
			printf("Connection closed\n");
			break;
		}
		else
		{
			printf("Recv failed: %d\n", WSAGetLastError());
			break;
		}
		
		if (SOCKET_ERROR == RecvResult)
		{
			printf("Send failed: %d\n", WSAGetLastError());
		}
	}
	/// Close the session
	close_session(SessionIndex);
	return 0;
}

string packetDecoder(string packet, int packetLength)
{
	//Get message out
	string decodedPacket = "";

	for (int i = 1; i < packetLength - 1; ++i)
	{
		decodedPacket += packet[i] - 1;
	}

	return string(decodedPacket);
} 

string packetEncoder(string packet, int packetLength)
{
	//Encode by adding 1 to every char
	for (int i = 0; i < packetLength; ++i)
	{
		packet[i] += 1;
	}

	string EncodedMessage;
	EncodedMessage += "<" + string(packet) + ">";

	return EncodedMessage;
}
///////////////////////////////////////////////////////////////////////////////
// ** CAUSION **                                                             //
// YOU SHOULD NOT TOUCH ANYTHING INSIDE THIS HEADER FILE.                    //
///////////////////////////////////////////////////////////////////////////////

// Simple Network library for DM2241 Multiplayer Game Programming.
//

#ifndef _HNET_H
#define _HNET_H
#pragma once

#include <WinSock2.h>
#include <thread>
#include <list>

#include "Session.h"
#include "ProcessSession.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


namespace HNet
{
    void debug_print_packet( char Buffer[], int BufferLength );
    void debug_print_fdset( fd_set FdSets );
}


namespace HNet
{
#define PACKET_HEADER           0xFFFB
#define PACKET_HEADER_SIZE      2
#define PACKET_HEADER_DATATYPE  unsigned short int
#define PACKET_TRAILER          0xFFFA
#define PACKET_TRAILER_SIZE     2
#define PACKET_TRAILER_DATATYPE unsigned short int
#define PACKET_LENGTH_SIZE      2
#define PACKET_LENGTH_DATATYPE  unsigned short int
}


namespace HNet
{
    // Error codes for HNet.
    enum
    {
        HNET_ERROR_NOERROR = 0,
        HNET_ERROR_WSASTARTUP,		    // 1
        HNET_ERROR_WRONGAPPTYPE,		    // 2
        HNET_ERROR_SOCKETFAILED,		    // 3
        HNET_ERROR_BINDFAILED,		    // 4
        HNET_ERROR_LISTENFAILED,          // 5
        HNET_ERROR_CREATERECVTHREADFAILD, // 6
        HNET_ERROR_SELECTRETURNEDERROR,   // 7
        HNET_ERROR_ACCEPTFAILED,          // 8
    };

    // App Type.
    enum
    {
        APPTYPE_SERVER = 1,
        APPTYPE_CLIENT
    };

    // Protocol Type.
    enum
    {
        PROTOCOL_TCP = 1,
        PROTOCOL_UDP
    };
}

namespace HNet
{
    //-------------------------
    // Class definitions for Network Objects.
    class NetLib
    {
        private:
            int     AppType;
            int     ProtocolType;
            int     PortNumber;

            WSADATA WsaData;
            SOCKET  MainSocket;

            HANDLE  RecvThreadHandle;
            DWORD   RecvThreadID;

            int ErrorCode;

        // Constructor and Destructor.
        public:
            NetLib();
            ~NetLib();

        // Getters & Setters.
        protected:
            SOCKET GetMainSocket( void );
            int    GetAppType( void );
            int    GetProtocolType( void );
            int    GetPortNumber( void );

            void   SetRecvThreadHandle( HANDLE hThread );
            HANDLE GetRecvThreadHandle( void );

            void   SetRecvThreadID( DWORD ThreadID );
            DWORD  GetRecvThreadID( void );

        private:
            int EncodePacket( struct _PacketMessage PacketMessage, char Packet[] );
            int DecodePacket( char Packet[], struct _PacketMessage PacketMessage );

        public:
            void SetErrorCode( int ErrorCode );

            int   GetErrorCode( void );
            char *GetErrorMessage( void );

        protected:
            int InitHNet( int AppType, int ProtocolType, int PortNumber );

        // General functions for Winsock.
        public:
            int SendPacket( SOCKET SendSocket, struct _PacketMessage PacketMessage );
    };
}


#endif
///////////////////////////////////////////////////////////////////////////////
// ** CAUSION **                                                             //
// YOU SHOULD NOT TOUCH ANYTHING INSIDE THIS HEADER FILE.                    //
///////////////////////////////////////////////////////////////////////////////

#ifndef _SERVERNETWORK_H
#define _SERVERNETWORK_H
#pragma once

#include "NetLib.h"
#include "ServerNetwork.h"


//-------------------------
// Class for server network
namespace HNet
{
    class _ServerNetwork : public NetLib
    {
        private:
            _SessionList        SessionList;
            struct _ProcessSessionList ToProcessList;

        public:
            _ServerNetwork();
            ~_ServerNetwork();

        private:
            int CloseSessionByIndex( int SessionIndex );

        public:
            bool InitNet( int AppType, int ProtocolType, int PortNumber );
            int GetConnectedCount( void );
            int CloseSession( _SessionNode *SessionNode );

            SOCKET GetMainSocket() { return NetLib::GetMainSocket(); }
            _SessionList *GetSessionList() { return &SessionList; }
            _ProcessSessionList *GetProcessList() { return &ToProcessList;  }

            int SendPacket( int SessionIndex, struct _PacketMessage PacketMessage );
            int SendPacketToAll( _PacketMessage PacketMessage );
            int SendPacketToAllExcept( _PacketMessage PacketMessage, int SessionIndex );
    };
}

namespace HNet
{
    DWORD WINAPI ServerRecvThread( void *arg );
}

#endif

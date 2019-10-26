#ifndef _CLIENTNETWORK_H
#define _CLIENTNETWORK_H

#pragma once

#include "NetLib.h"


///-------------------------
/// Class for client network
namespace HNet
{
    class _ClientNetwork : public NetLib
    {
        private:
            _SessionNode Session;
            _ProcessSessionList ToProcessList;

        public:
            _ClientNetwork();
            ~_ClientNetwork();

        public:
            SOCKET GetSocket( void ) { return GetMainSocket(); }
            _SessionNode *GetSession( void ) { return &Session; }
            _ProcessSessionList *GetProcessList( void ) { return &ToProcessList; }

        public:
            bool InitNet( int AppType, int ProtocolType, char *ServerIpAddress, int PortNumber );
            int ConnectToServer( char *ServerIPAddress, int PortNumber );
            int SendPacket( struct _PacketMessage PacketMessage );

            int CheckPacketRecevied( void );

    };
}

namespace HNet
{
    DWORD WINAPI RunClientThread( void *arg );
}


#endif

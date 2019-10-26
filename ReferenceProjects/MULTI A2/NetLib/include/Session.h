///////////////////////////////////////////////////////////////////////////////
// ** CAUSION **                                                             //
// YOU SHOULD NOT TOUCH ANYTHING INSIDE THIS HEADER FILE.                    //
///////////////////////////////////////////////////////////////////////////////

#ifndef _SESSION_H
#define _SESSION_H
#pragma once

#include "Global.h"
#include <WinSock2.h>
#include <cassert>

#define RECV_BUFSIZE    4096

namespace HNet
{
    // ---------------------------------------
    // Data structures for Session Management.

    class _SessionNode
    {
        private:
            int         Index;
            SOCKET      CommSocket;
            SOCKADDR_IN SessionAddress;

            char        RecvBuffer[RECV_BUFSIZE];
            int         RecvBufferWritePos;

            _SessionNode *Prev;
            _SessionNode *Next;

        public:
            _SessionNode();
            ~_SessionNode();

            void SetIndex( int Index );
            int  GetIndex( void );
            void   SetCommSocket( SOCKET CommSocket );
            SOCKET GetCommSocket( void );
            void        SetSessionAddress( SOCKADDR_IN SessionAddress );
            SOCKADDR_IN GetSessionAddress( void );

            void ClearRecvBuffer( void );
            int  AddToRecvBuffer( char NewBuffer[], int NewBufferLength );
            char *GetRecvBuffer( void );
            char *GetRecvBuffer( int Pos );
            int  ShiftRecvBuffer( int ShiftSize );

            void SetRecvBufferWritePos( int Pos );
            int  GetRecvBufferWritePos( void );                             // Same as the length of the data inside the buffer.

            int  CheckCompletedPacket( char CompletedPacket[], int *CompletedPacketLength );

            void Clear( void );
            void CloseSession( void );

            void SetPrev( _SessionNode *Prev );
            _SessionNode *GetPrev( void );
            void SetNext( _SessionNode *Next );
            _SessionNode *GetNext( void );

            void SetNewConnectedSession( SOCKET Socket, SOCKADDR_IN Address );
    };

    class _SessionList
    {
        private:
            _SessionNode *IndexList[MAX_CONNECTION + 1];

        public:
            struct _ListData {
                private:
                    int NodeCount;
                    _SessionNode *Head;
                    _SessionNode *Tail;

                public:
                    int           GetNodeCount( void );
                    void          SetNodeCount( int Count );
                    _SessionNode *GetHead( void );
                    void          SetHead( _SessionNode *Node );
                    _SessionNode *GetTail( void );
                    void          SetTail( _SessionNode *Node );

                public:
                    int AttachNode( _SessionNode *Node );
                    _SessionNode *DetachFirstNode( void );
                    _SessionNode *DetachLastNode( void );
                    int DetachNode( _SessionNode *Node );
                    int GetSessionIndexBySocket( SOCKET Socket );
                    _SessionNode *GetSessionNodeBySocket( SOCKET Socket );
            } ActiveList, EmptyList;

        public:
            _SessionList();
            ~_SessionList();

        public:
            _SessionNode *GetSessionNodeByIndex( int Index );
    };
}

#endif

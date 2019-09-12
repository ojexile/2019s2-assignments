///////////////////////////////////////////////////////////////////////////////
// ** CAUSION **                                                             //
// YOU SHOULD NOT TOUCH ANYTHING INSIDE THIS HEADER FILE.                    //
///////////////////////////////////////////////////////////////////////////////

#ifndef _PROCESSSESSION_H
#define _PROCESSSESSION_H
#pragma once

#include <WinSock2.h>

#define SEND_BUFSIZE    512
#define MAX_STRING_LENGTH_FOR_PACKET 200

namespace HNet
{

    enum
    {
        SESSION_STATE_EMPTY = 0,            // 0
        SESSION_STATE_CLOSEREDY,            // 1
        SESSION_STATE_NEWCONNECTION,        // 2
        SESSION_STATE_READPACKET,           // 3
    };

    struct GetString {
        char str[MAX_STRING_LENGTH_FOR_PACKET + 1];
        WORD str_len;

        GetString( WORD len )
        {
            str_len = len;
        }
    };

    struct _PacketMessage
    {
        int   BufferWritePos;         // Same as the length of the data inside the buffer.
        int   BufferReadPos;
        char  Buffer[SEND_BUFSIZE];

        _PacketMessage() : BufferWritePos( 0 ), BufferReadPos( 0 )
        {
        }
        ~_PacketMessage()
        {
            Reset();
        }

        void Reset( void )
        {
            BufferWritePos = 0;
            BufferReadPos = 0;
        }

        char *GetBuffer( void ) { return (char *)Buffer; }
        int GetBufferLength( void ) { return BufferWritePos; }

        int DecodePacket( char Packet[], int PacketLength, struct _PacketMessage *PacketMessage );
        int CopyBufferTo( char *Dest );
        int CopyBufferFrom( char *Origin, int OriginLength );

        WORD StrManager( char* copy, char* source, WORD len )
        {
            if( _msize( copy ) <= len )
            {
                return 0;
            }

            WORD itr = 0;
            WORD rtv;

            itr = (WORD)strlen( source );
            strncpy_s( copy, _msize( copy ), source, len );

            if( itr > len )
                copy[len] = '\0';
            else
                copy[itr] = '\0';

            rtv = itr + 1;

            return rtv;
        }

        template <typename T>
        _PacketMessage& Add( T & data )
        {
            int DataSize = ( int )sizeof( T );
            CopyMemory( (PVOID)&Buffer[BufferWritePos], ( CONST PVOID )&data, DataSize );
            BufferWritePos += DataSize;

            return *this;
        }

        _PacketMessage& AddString( const char* & data )
        {
            int StringLength = (int)strlen( data ) + 1;
            lstrcpy( (LPTSTR)&Buffer[BufferWritePos], (LPCTSTR)data );
            BufferWritePos += StringLength;
            return *this;
        }

        template <typename T>
        _PacketMessage& Fetch( T & data )
        {
            int DataSize = ( int )sizeof( T );
            CopyMemory( (PVOID)&data, ( CONST PVOID )&Buffer[BufferReadPos], DataSize );
            BufferReadPos += DataSize;
            return *this;
        }

        _PacketMessage& FetchByte( unsigned char* data )
        {
            CopyMemory( (PVOID)data, ( CONST PVOID )&Buffer[BufferReadPos], 1 );
            BufferReadPos += 1;
            return *this;
        }

        _PacketMessage& FetchString( GetString& str )
        {
            int DataSize = str.str_len + 1;
            StrManager( str.str, (char *)&Buffer[BufferReadPos], str.str_len );
            BufferReadPos += DataSize;
            return *this;
        }

        _PacketMessage& FetchString( const char* & data )
        {
            int DataSize = (int)strlen( &Buffer[BufferReadPos] ) + 1;
            lstrcpy( (LPTSTR)data, (LPCTSTR)&Buffer[BufferReadPos] );
            BufferReadPos += DataSize;
            return *this;
        }

        template <typename T>
        _PacketMessage& operator << ( const T & data   ) { return Add( data );                      }
        _PacketMessage& operator << ( const char* data ) { return AddString( data );                }
        _PacketMessage& operator << ( char* data       ) { return AddString( (const char* &)data ); }

        template <typename T>
        _PacketMessage& Write( const T & data   ) { return Add( data );                      }
        _PacketMessage& Write( const char* data ) { return AddString( data );                }
        _PacketMessage& Write( char* data       ) { return AddString( (const char* &)data ); }

        template <typename T>
        _PacketMessage& operator >> ( T & data         ) { return Fetch( data );                      }
        _PacketMessage& operator >> ( const char* data ) { return FetchString( data );                }
        _PacketMessage& operator >> ( char* data       ) { return FetchString( (const char* &)data ); }
        _PacketMessage& operator >> ( GetString & data ) { return FetchString( data );                }

        template <typename T>
        _PacketMessage Read( const T &data    ) { return Fetch( data );                       }
        _PacketMessage Read( const char *data ) { return FetchString( data );                 }
        _PacketMessage Read( char *data       ) { return FetchString( (const char * &)data ); }
        _PacketMessage Read( GetString &data  ) { return FetchString( data );                 }
    };

    struct _ProcessSession {
        int          SessionState;
        int          SessionIndex;
        SOCKADDR_IN  SessionAddress;
        struct _PacketMessage PacketMessage;

        struct _ProcessSession *Prev;
        struct _ProcessSession *Next;

        struct _ProcessSession()
        {
            SessionState = 0;
            SessionIndex = 0;
            Prev = NULL;
            Next = NULL;
        }
    };
    struct _ProcessSessionList {
        struct _ProcessSession *Head;
        struct _ProcessSession *Tail;

        struct _ProcessSessionList()
        {
            Head = NULL;
            Tail = NULL;
        }

        void Attach( _SessionNode *SessionNode, int State, int PacketLength, char Packet[] );
        struct _ProcessSession *GetFirstSession( void );
        void DeleteFirstSession( void );
    };
}


#endif
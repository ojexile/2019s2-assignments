#ifndef _PROCESS_RECEIVED_PACKET_H
#define _PROCESS_RECEIVED_PACKET_H
#pragma once


// Function declarations.
void ProcessReceivedPacket( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_EnterGame( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_Movement( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_Collided( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_NewMissile( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_MissileCollided( struct HNet::_ProcessSession *ToProcessSession );
void ProcessReceivedPacket_NewTimebomb(struct HNet::_ProcessSession *ToProcessSession);
void ProcessReceivedPacket_MedkitTaken(struct HNet::_ProcessSession *ToProcessSession);

#endif
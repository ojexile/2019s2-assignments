#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
	int x;
	int y;
	float width;
	float height;
	bool connected;

	Room(int _x, int _y, int _width, int _height);
};
#endif
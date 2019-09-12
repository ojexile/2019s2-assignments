#include "Room.h"

Room::Room(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = (float)_width;
	height = (float)_height;
	connected = false;
}
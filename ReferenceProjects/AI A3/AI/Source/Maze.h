#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <queue>
#include "Room.h"

struct MazePt
{
	int x, y;
	MazePt(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	void Set(int _x = 0, int _y = 0) {x = _x; y = _y;}
};

struct Connector
{
	int x, y;
	std::vector<int> connectingRegions;
	bool isDone;
	Connector(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	void Set(int _x = 0, int _y = 0) { x = _x; y = _y; }
};

class Maze
{
public:
	enum TILE_CONTENT
	{
		TILE_WALL = -1,
		TILE_FOG,
		TILE_EMPTY,
		TILE_WATER,
		TILE_TALLGRASS,
		TILE_FIRE,
		TILE_STAIRS,
	};
	enum DIRECTION
	{
		DIR_NONE,
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
	};
	Maze();
	~Maze();

	std::vector<TILE_CONTENT> m_grid;
	//-1 = path, >= 0 = rooms, -2 = merged
	std::vector<int> m_gridID;
	std::vector<Room*> rooms;
	TILE_CONTENT See(MazePt tile);
	
	void Generate(unsigned key, unsigned size, MazePt start, float wallLoad, int numTries);
	void MazeGeneratorRecursion(MazePt position, int size);
	bool Move(DIRECTION direction);
	unsigned GetKey();
	unsigned GetSize();
	MazePt GetCurr();
	int GetNumMove();
	void SetCurr(MazePt newCurr);
	void SetNumMove(int num);
	void DungeonGenerator(int mazeSize, int numTries);
	bool checkOverlap(Room* room1, Room* room2);
	void addRoomtoMap(int size, Room* room, int roomID);
	void connectRooms(int size);
	void BFSmerge(MazePt startpoint, int mazeSize);
	void eraseDeadEnds(int mazeSize);
	int getTileCost(TILE_CONTENT tile);
private:
	//Do not make these public
	unsigned m_key;
	unsigned m_size;
	MazePt m_curr;
	int m_numMove;
	std::vector<bool> m_visited;
	std::queue<MazePt> m_queue;
	std::vector<bool> merged;
};

#endif
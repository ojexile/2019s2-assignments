#include "Maze.h"
#include <iostream>
#include <algorithm>
#include "MyMath.h"
#include "Application.h"

Maze::Maze()
{
}

Maze::~Maze()
{
}

void Maze::Generate(unsigned key, unsigned size, MazePt start, float wallLoad, int numTries)
{
	m_grid.resize(size * size);
	std::fill(m_grid.begin(), m_grid.end(), Maze::TILE_WALL);
	m_gridID.resize(size * size);
	std::fill(m_gridID.begin(), m_gridID.end(), -10);
	m_visited.resize(size * size);
	std::fill(m_visited.begin(), m_visited.end(), false);
	merged.resize(size * size);
	std::fill(merged.begin(), merged.end(), false);
	rooms.clear();
	
	while (m_queue.size() > 0)
		m_queue.pop();

	if (size == 0)
		return;
	DungeonGenerator(size, numTries);

	/*std::cout << "Maze " << key << std::endl;
	for (int row = (int)size - 1; row >= 0; --row)
	{
		for (int col = 0; col < (int)size; ++col)
		{
			if (m_grid[row * size + col] == TILE_WALL)
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout << std::endl;
	}*/

	m_key = key;
	m_size = size;
	m_numMove = 0;
}

void Maze::MazeGeneratorRecursion(MazePt position, int size)
{
	//Generate 4 directions in random order
	int DirArray[] = {1,2,3,4};
	std::random_shuffle(std::begin(DirArray), std::end(DirArray));

	for (int i = 0; i < sizeof(DirArray) / sizeof(int); ++i)
	{
		MazePt nextPos;
		switch (DirArray[i])
		{
			//Up
		case 1:		
			nextPos.Set(position.x, position.y + 2);
			if (nextPos.y >= size)
				continue;

			if (m_grid[nextPos.x + nextPos.y * size] != TILE_EMPTY)
			{
				m_grid[position.x + (position.y + 1) * size] = TILE_EMPTY;
				m_grid[position.x + (position.y + 2) * size] = TILE_EMPTY;
				m_gridID[position.x + (position.y + 1) * size] = -1;
				m_gridID[position.x + (position.y + 2) * size] = -1;
				MazeGeneratorRecursion(nextPos, size);
			}
			break;
			//Down
		case 2:
			nextPos.Set(position.x, position.y - 2);
			if (nextPos.y < 0)
				continue;

			if (m_grid[nextPos.x + nextPos.y * size] != TILE_EMPTY)
			{
				m_grid[position.x + (position.y - 1) * size] = TILE_EMPTY;
				m_grid[position.x + (position.y - 2) * size] = TILE_EMPTY;
				m_gridID[position.x + (position.y - 1) * size] = -1;
				m_gridID[position.x + (position.y - 2) * size] = -1;
				MazeGeneratorRecursion(nextPos, size);
			}
			break;
			//Left
		case 3:
			nextPos.Set(position.x - 2, position.y);
			if (nextPos.x < 0)
				continue;

			if (m_grid[nextPos.x + nextPos.y * size] != TILE_EMPTY)
			{
				m_grid[(position.x - 1) + position.y * size] = TILE_EMPTY;
				m_grid[(position.x - 2) + position.y * size] = TILE_EMPTY;
				m_gridID[(position.x - 1) + position.y * size] = -1;
				m_gridID[(position.x - 2) + position.y * size] = -1;
				MazeGeneratorRecursion(nextPos, size);
			}
			break;
			//Right
		case 4:
			nextPos.Set(position.x + 2, position.y);
			if (nextPos.x >= size)
				continue;

			if (m_grid[nextPos.x + nextPos.y * size] != TILE_EMPTY)
			{
				m_grid[(position.x + 1) + position.y * size] = TILE_EMPTY;
				m_grid[(position.x + 2) + position.y * size] = TILE_EMPTY;
				m_gridID[(position.x + 1) + position.y * size] = -1;
				m_gridID[(position.x + 2) + position.y * size] = -1;
				MazeGeneratorRecursion(nextPos, size);
			}
			break;
		}
	}
}

Maze::TILE_CONTENT Maze::See(MazePt tile)
{
	return m_grid[tile.x + tile.y * m_size];
}

unsigned Maze::GetKey()
{
	return m_key; 
}

unsigned Maze::GetSize()
{
	return m_size;
}

MazePt Maze::GetCurr()
{
	return m_curr;
}

int Maze::GetNumMove()
{
	return m_numMove;
}

void Maze::SetCurr(MazePt newCurr)
{
	++m_numMove;
	m_curr = newCurr;
}

void Maze::SetNumMove(int num)
{
	m_numMove = num;
}

bool Maze::Move(DIRECTION direction)
{
	++m_numMove;
	MazePt temp = m_curr;
	switch (direction)
	{
	case DIR_LEFT:
		if (temp.x == 0)
			return false;
		temp.x -= 1;
		break;
	case DIR_RIGHT:
		if (temp.x == (int)m_size - 1)
			return false;
		temp.x += 1;
		break;
	case DIR_UP:
		if (temp.y == (int)m_size - 1)
			return false;
		temp.y += 1;
		break;
	case DIR_DOWN:
		if (temp.y == 0)
			return false;
		temp.y -= 1;
		break;
	}
	int tempId = temp.y * m_size + temp.x;
	if (m_grid[tempId] == TILE_WALL)
		return false;
	m_curr = temp;
	return true;
}


void Maze::DungeonGenerator(int mazeSize, int numTries)
{
	//GENERATE ROOMS
	int roomID = 0;
	for (int i = 0; i < numTries; ++i)
	{
		int size;
		if (Math::RandIntMinMax(1, 2) == 1)
			size = 3;
		else
			size = 5;

		int additionalSide;
		if (Math::RandIntMinMax(1, 2) == 1)
			additionalSide = 0;
		else
			additionalSide = 2;

		int width, height;
		width = height = size;

		if (Math::RandIntMinMax(1, 2) == 1)
			width += additionalSide;
		else
			height += additionalSide;

		int x = Math::RandIntMinMax(0, (int)((mazeSize - width - 1) * 0.5f)) * 2 + 1;
		int y = Math::RandIntMinMax(0, (int)((mazeSize - height - 1) * 0.5f)) * 2 + 1;

		//x and y of room is bottom Left corner
		Room* newRoom = new Room(x, y, width, height);

		bool overlap = false;
		//Check overlap with other rooms
		for (unsigned int j = 0; j < rooms.size(); ++j)
		{
			overlap = checkOverlap(newRoom, rooms[j]);
			if (overlap)
				break;
		}

		if (overlap)
			continue;

		rooms.push_back(newRoom);
		addRoomtoMap(mazeSize, newRoom, roomID);
		roomID++;
	}

	//Fill in spaces with paths
	for (int y = 1; y < mazeSize; y += 2) 
	{
		for (int x = 1; x < mazeSize; x += 2)
		{
			MazePt pos(x, y);
			if (m_grid[pos.x + pos.y * mazeSize] != TILE_WALL) 
				continue;

			MazeGeneratorRecursion(pos, mazeSize);
		}
	}

	//Connect the rooms
	connectRooms(mazeSize);

	//Erase deadends
	eraseDeadEnds(mazeSize);
	
	//Set Stairs
	int randomRoom = Math::RandIntMinMax(0, rooms.size() - 1);
	int randomX = Math::RandIntMinMax(0, (int)rooms[randomRoom]->width - 1);
	int randomY = Math::RandIntMinMax(0, (int)rooms[randomRoom]->height - 1);
	m_grid[(rooms[randomRoom]->x + randomX) + (rooms[randomRoom]->y + randomY) * mazeSize] = TILE_STAIRS;
}

bool Maze::checkOverlap(Room* room1, Room* room2)
{
	MazePt left1(room1->x, room1->y + (int)room1->height);
	MazePt right1(room1->x + (int)room1->width, room1->y);
	MazePt left2(room2->x, room2->y + (int)room2->height);
	MazePt right2(room2->x + (int)room2->width, room2->y);

	if (left1.x > right2.x || left2.x > right1.x)
		return false;

	if (left1.y < right2.y || left2.y < right1.y)
		return false;

	return true;
}

void Maze::addRoomtoMap(int size, Room* room, int roomID)
{
	MazePt BtmLeftCorner(room->x, room->y);

	for (int i = 0; i < room->height; ++i)
	{
		for (int j = 0; j < room->width; ++j)
		{
			int chance = Math::RandIntMinMax(1, 20);
			if (chance == 1 || chance == 2)
				m_grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + i) * size] = TILE_WATER;
			else if (chance == 3)
				m_grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + i) * size] = TILE_TALLGRASS;
			else if (chance == 4)
				m_grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + i) * size] = TILE_FIRE;
			else
				m_grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + i) * size] = TILE_EMPTY;

			m_gridID[BtmLeftCorner.x + j + (BtmLeftCorner.y + i) * size] = roomID;
		}
	}
}

void Maze::connectRooms(int size)
{
	std::vector<Connector*> connectors;

	for (int i = 1; i < size - 1; ++i)
	{
		for (int j = 1; j < size - 1; ++j)
		{
			if (m_grid[i + j * size] != TILE_WALL)
				continue;

			std::vector<int> totalConnections;
			//Check in all directions			
			//UP
			MazePt nextDir(i, j);
			nextDir.y++;
			if (m_grid[nextDir.x + nextDir.y * size] != TILE_WALL)
				totalConnections.push_back(m_gridID[nextDir.x + nextDir.y * size]);
				
			//DOWN
			nextDir.Set(i, j);
			nextDir.y--;
			if (m_grid[nextDir.x + nextDir.y * size] != TILE_WALL)
				totalConnections.push_back(m_gridID[nextDir.x + nextDir.y * size]);

			//LEFT
			nextDir.Set(i, j);
			nextDir.x--;
			if (m_grid[nextDir.x + nextDir.y * size] != TILE_WALL)
				totalConnections.push_back(m_gridID[nextDir.x + nextDir.y * size]);

			//RIGHT
			nextDir.Set(i, j);
			nextDir.x++;
			if (m_grid[nextDir.x + nextDir.y * size] != TILE_WALL)
				totalConnections.push_back(m_gridID[nextDir.x + nextDir.y * size]);

			if (totalConnections.size() < 2)
				continue;

			Connector* pos = new Connector(i, j);
			pos->connectingRegions = totalConnections;
			pos->isDone = false;
			connectors.push_back(pos);
		}
	}

	merged.resize(size * size);
	std::fill(merged.begin(), merged.end(), false);

	//Random a connector to open and make that region the main region
	int randNum = Math::RandIntMinMax(0, rooms.size() - 1);
	Connector* current = connectors[randNum];
	m_grid[current->x + current->y * size] = TILE_EMPTY;
	merged[current->x + current->y * size] = true;
	for (unsigned int i = 0; i < current->connectingRegions.size(); ++i)
	{
		if (current->connectingRegions[i] >= 0)
			rooms[current->connectingRegions[i]]->connected = true;
	}
	connectors.erase(connectors.begin() + randNum);

	while (connectors.size() > 0)
	{
		//BFS to merge all connected regions
		BFSmerge(MazePt(current->x, current->y), size);
		current->isDone = true;

		//erase done connectors
		for (std::vector<Connector*>::iterator it = connectors.begin(); it != connectors.end();)
		{
			if ((*it)->isDone)
			{
				delete *it;
				it = connectors.erase(it);
			}
			else
			{
				++it;
			}
		}

		//Find a random connector that connects to the main region and open it
		std::vector<Connector *> connectingtoMain;
		for (unsigned int i = 0; i < connectors.size(); ++i)
		{
			Connector* currConnector = connectors[i];

			int totalConnections = 0;
			if (merged[currConnector->x - 1 + currConnector->y * size] == true)
				totalConnections++;

			if (merged[currConnector->x + 1 + currConnector->y * size] == true)
				totalConnections++;

			if (merged[currConnector->x + (currConnector->y - 1) * size] == true)
				totalConnections++;

			if (merged[currConnector->x + (currConnector->y + 1) * size] == true)
				totalConnections++;

			if (totalConnections == 1)
				connectingtoMain.push_back(currConnector);
		}

		//Select 1 of the connectors and open it
		if (connectingtoMain.size() > 0)
		{
			int randomNum = Math::RandIntMinMax(0, connectingtoMain.size() - 1);
			current = connectingtoMain[randomNum];
			m_grid[current->x + current->y * size] = TILE_EMPTY;
			merged[current->x + current->y * size] = true;

			//Set regions to done
			for (unsigned int i = 0; i < current->connectingRegions.size(); ++i)
			{
				if (current->connectingRegions[i] >= 0)
					rooms[current->connectingRegions[i]]->connected = true;				
			}
		}
		else
		{
			for (unsigned int i = 0; i < connectors.size(); ++i)
			{
				Connector* currConnector = connectors[i];
				if (Math::RandIntMinMax(1, 30) == 1)
				{
					m_grid[currConnector->x + currConnector->y * size] = TILE_EMPTY;
					merged[currConnector->x + currConnector->y * size] = true;
				}
				currConnector->isDone = true;
			}

			connectors.clear();
			break;
		}
	}
}

void Maze::BFSmerge(MazePt startpoint, int mazeSize)
{
	std::fill(m_visited.begin(), m_visited.end(), false);
	while (!m_queue.empty())
		m_queue.pop();
	m_queue.push(startpoint);
	while (!m_queue.empty())
	{
		MazePt curr = m_queue.front();
		m_queue.pop();
		//UP
		if (curr.y < mazeSize)
		{
			MazePt next(curr.x, curr.y + 1);
			if (!m_visited[next.y * mazeSize + next.x] && m_grid[next.y * mazeSize + next.x] != Maze::TILE_WALL)
			{
				m_queue.push(next);
				m_visited[next.y * mazeSize + next.x] = true;
				merged[next.x + next.y * mazeSize] = true;
			}
		}
		//DOWN
		if (curr.y > 0)
		{
			MazePt next(curr.x, curr.y - 1);
			if (!m_visited[next.y * mazeSize + next.x] && m_grid[next.y * mazeSize + next.x] != Maze::TILE_WALL)
			{
				m_queue.push(next);
				m_visited[next.y * mazeSize + next.x] = true;
				merged[next.x + next.y * mazeSize] = true;
			}
		}
		//LEFT
		if (curr.x > 0)
		{
			MazePt next(curr.x - 1, curr.y);
			if (!m_visited[next.y * mazeSize + next.x] && m_grid[next.y * mazeSize + next.x] != Maze::TILE_WALL)
			{
				m_queue.push(next);
				m_visited[next.y * mazeSize + next.x] = true;
				merged[next.x + next.y * mazeSize] = true;
			}
		}
		//RIGHT
		if (curr.x < mazeSize)
		{
			MazePt next(curr.x + 1, curr.y);
			if (!m_visited[next.y * mazeSize + next.x] && m_grid[next.y * mazeSize + next.x] != Maze::TILE_WALL)
			{
				m_queue.push(next);
				m_visited[next.y * mazeSize + next.x] = true;
				merged[next.x + next.y * mazeSize] = true;
			}
		}
	}
}

void Maze::eraseDeadEnds(int mazeSize)
{
	bool cleanedMaze = false;

	while (!cleanedMaze)
	{
		cleanedMaze = true;
		for (int i = 1; i < mazeSize - 1; ++i)
		{
			for (int j = 1; j < mazeSize - 1; ++j)
			{
				if (m_grid[i + j * mazeSize] == TILE_WALL)
					continue;

				int totalExits = 0;
				//UP
				MazePt nextDir(i, j);
				nextDir.y++;
				if (m_grid[nextDir.x + nextDir.y * mazeSize] != TILE_WALL)
					totalExits++;

				//DOWN
				nextDir.Set(i, j);
				nextDir.y--;
				if (m_grid[nextDir.x + nextDir.y * mazeSize] != TILE_WALL)
					totalExits++;

				//LEFT
				nextDir.Set(i, j);
				nextDir.x--;
				if (m_grid[nextDir.x + nextDir.y * mazeSize] != TILE_WALL)
					totalExits++;

				//RIGHT
				nextDir.Set(i, j);
				nextDir.x++;
				if (m_grid[nextDir.x + nextDir.y * mazeSize] != TILE_WALL)
					totalExits++;

				nextDir.Set(i, j);
				if (totalExits <= 1)
				{
					m_grid[nextDir.x + nextDir.y * mazeSize] = TILE_WALL;
					cleanedMaze = false;
				}				
			}
		}
	}	
}

int Maze::getTileCost(TILE_CONTENT tile)
{
	switch (tile)
	{
	case TILE_WALL:
		return 1000;
	case TILE_EMPTY:
		return 1;
	case TILE_WATER:
		return 2;
	case TILE_TALLGRASS:
		return 3;
	case TILE_FIRE:
		return 2;
	case TILE_STAIRS:
		return 1;
	}

	return 0;
}
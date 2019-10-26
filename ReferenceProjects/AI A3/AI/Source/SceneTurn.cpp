#include "SceneTurn.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneData.h"
#include <string>
#include <sstream>

SceneTurn::SceneTurn()
{
}

SceneTurn::~SceneTurn()
{
}

void SceneTurn::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_noGrid = 15;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2; 

	SceneData::GetInstance()->setNoGrid(m_noGrid);
	SceneData::GetInstance()->setGridSize(m_worldHeight / SceneData::GetInstance()->getNoGrid());

	m_start.Set(0, 0);
	m_mazeKey = 0;
	m_wallLoad = 0.3f;
	m_maze.Generate(m_mazeKey, m_noGrid, m_start, m_wallLoad, 300); //Generate new maze
	m_myGrid.resize(m_noGrid * m_noGrid);
	m_visited.resize(m_noGrid * m_noGrid);
	m_previous.resize(m_noGrid * m_noGrid);
	std::fill(m_myGrid.begin(), m_myGrid.end(), Maze::TILE_FOG);
	std::fill(m_visited.begin(), m_visited.end(), false);
	m_myGrid[m_start.y * m_noGrid + m_start.x] = Maze::TILE_EMPTY;

	SceneData::GetInstance()->mazeInfo = m_maze;

	m_turn = 0;
	timer = 0;

	//Spawn player object
	player = FetchGO(GameObject::GO_PLAYER);
	player->type = GameObject::GO_PLAYER;
	player->grid.resize(m_noGrid * m_noGrid);
	player->previous.resize(m_noGrid * m_noGrid);
	player->visited.resize(m_noGrid * m_noGrid);
	std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
	std::fill(player->visited.begin(), player->visited.end(), false);
	std::fill(player->previous.begin(), player->previous.end(), MazePt(0, 0));
	player->active = true;

	//set go->curr to an empty tile in one of the rooms
	int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	player->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
	player->pos.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);
	player->target.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);
	player->damage = 10;
	player->hp = 100;
	player->maxHp = 100;
	player->oranBerryCount = 3;

	playerTurn = true;
	if (RoomVisibilityCheck(player) == false)
		DFSlimit(player, 3);
	toggleMap = false;
	movingObjects = false;
	stageNum = 1;

	//Spawn the key
	keyTaken = false;
	randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	GameObject* key = FetchGO(GameObject::GO_KEY);
	key->type = GameObject::GO_KEY;
	key->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);

	//Spawn Enemies
	for (int i = 0; i < 5; ++i)
	{
		GameObject *go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
		go->type = GameObject::GO_MONSTER_BULBASAUR;
		go->grid.resize(m_noGrid * m_noGrid);
		go->previous.resize(m_noGrid * m_noGrid);
		go->visited.resize(m_noGrid * m_noGrid);
		std::fill(go->grid.begin(), go->grid.end(), Maze::TILE_FOG);
		std::fill(go->visited.begin(), go->visited.end(), false);
		std::fill(go->previous.begin(), go->previous.end(), MazePt(0, 0));
		go->active = true;
		go->hp = 30;
		go->maxHp = 30;
		go->damage = 5;
		go->targetGO = NULL;
		go->sm->SetNextState("Moving");

		SceneData::GetInstance()->setMonsterCount(SceneData::GetInstance()->getMonsterCount() + 1);
		int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
		int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
		int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
		go->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
		go->pos.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		go->target.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		if (RoomVisibilityCheck(go) == false)
			DFSlimit(go, 4);
	}

	//Spawn Oran Berries
	for (int i = 0; i < m_noGrid; ++i)
	{
		for (int j = 0; j < m_noGrid; ++j)
		{
			if (m_maze.m_grid[i + j * m_noGrid] != Maze::TILE_WALL)
			{
				if (Math::RandIntMinMax(1, 50) == 1)
				{
					bool canSpawn = true;
					//Check for any objects in that location
					for (unsigned int k = 0; k < m_goList.size(); ++k)
					{
						GameObject* go = m_goList[k];
						if (go->active)
						{
							if (go->type == GameObject::GO_KEY ||
								go->type == GameObject::GO_ORAN_BERRY)
							{
								if (go->curr.x == i && go->curr.y == j)
								{
									canSpawn = false;
								}
							}							
						}
					}

					if (canSpawn)
					{
						GameObject* berry = FetchGO(GameObject::GO_ORAN_BERRY);
						berry->type = GameObject::GO_ORAN_BERRY;
						berry->curr.Set(i, j);
					}
				}
			}
		}
	}
}

bool SceneTurn::Handle(Message *message)
{
	return false;
}

GameObject* SceneTurn::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && type == go->type)
		{
			go->active = true;
			go->pos.Set(0, 0, distance(m_goList.begin(), it) * 0.0001f);
			return go;
		}
	}

	for (unsigned i = 0; i < 5; ++i)
	{
		GameObject *go = new GameObject(type);
		m_goList.push_back(go);
	}
	return FetchGO(type);
}

void SceneTurn::DFSlimit(GameObject* go, int limit)
{
	limit--;
	if (limit <= 0)
		return;

	go->visited[go->curr.y * m_noGrid + go->curr.x] = true;
	go->grid[go->curr.y * m_noGrid + go->curr.x] = m_maze.See(go->curr);

	//UP
	if (go->curr.y < m_noGrid - 1)
	{
		MazePt next(go->curr.x, go->curr.y + 1);
		if (go->visited[next.y * m_noGrid + next.x] == false)
		{
			go->grid[next.x + next.y * m_noGrid] = m_maze.See(next);
			if (go->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x, next.y - 1);
			}
		}
	}
	//DOWN
	if (go->curr.y > 0)
	{
		MazePt next(go->curr.x, go->curr.y - 1);
		if (go->visited[next.y * m_noGrid + next.x] == false)
		{
			go->grid[next.x + next.y * m_noGrid] = m_maze.See(next);
			if (go->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x, next.y + 1);
			}
		}
	}
	//LEFT
	if (go->curr.x > 0)
	{
		MazePt next(go->curr.x - 1, go->curr.y);
		if (go->visited[next.y * m_noGrid + next.x] == false)
		{
			go->grid[next.x + next.y * m_noGrid] = m_maze.See(next);
			if (go->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x + 1, next.y);
			}
		}
	}
	//RIGHT
	if (go->curr.x < m_noGrid - 1)
	{
		MazePt next(go->curr.x + 1, go->curr.y);
		if (go->visited[next.y * m_noGrid + next.x] == false)
		{
			go->grid[next.x + next.y * m_noGrid] = m_maze.See(next);
			if (go->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x - 1, next.y);
			}
		}
	}
}

void SceneTurn::DFSOnce(GameObject* go)
{
	go->stack.push_back(go->curr);
	go->visited[go->curr.x + go->curr.y * m_noGrid] = true;

	//UP
	MazePt nextPos;
	nextPos.Set(go->curr.x, go->curr.y + 1);
	int index = nextPos.x + nextPos.y * m_noGrid;

	if (nextPos.y < m_noGrid && go->visited[index] == false)
	{
		go->grid[index] = m_maze.See(nextPos);
		if (go->grid[index] == Maze::TILE_EMPTY)
		{
			go->curr = nextPos;
			return;
		}
	}
	
	//DOWN
	nextPos.Set(go->curr.x, go->curr.y - 1);
	index = nextPos.x + nextPos.y * m_noGrid;
	if (nextPos.y >= 0 && go->visited[index] == false)
	{
		go->grid[index] = m_maze.See(nextPos);
		if (go->grid[index] == Maze::TILE_EMPTY)
		{
			go->curr = nextPos;
			return;
		}
	}

	//LEFT
	nextPos.Set(go->curr.x - 1, go->curr.y);
	index = nextPos.x + nextPos.y * m_noGrid;
	if (nextPos.x >= 0 && go->visited[index] == false)
	{
		go->grid[index] = m_maze.See(nextPos);
		if (go->grid[index] == Maze::TILE_EMPTY)
		{
			go->curr = nextPos;
			return;
		}
	}

	//RIGHT
	nextPos.Set(go->curr.x + 1, go->curr.y);
	index = nextPos.x + nextPos.y * m_noGrid;
	if (nextPos.x < m_noGrid && go->visited[index] == false)
	{
		go->grid[index] = m_maze.See(nextPos);
		if (go->grid[index] == Maze::TILE_EMPTY)
		{
			go->curr = nextPos;
			return;
		}
	}

	go->stack.pop_back();

	if (!go->stack.empty())
	{
		go->curr = go->stack.back();
		go->stack.pop_back();
		return;
	}
	else
	{
		go->mapReadFinished = true;
	}
}

void SceneTurn::DFS(MazePt curr)
{
	m_visited[curr.y * m_noGrid + curr.x] = true;
	//UP
	if(curr.y < m_noGrid - 1)
	{
		MazePt next(curr.x, curr.y + 1);
		if (!m_visited[next.y * m_noGrid + next.x])
		{
			if (m_maze.Move(Maze::DIR_UP) == true)
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_EMPTY;
				DFS(next);
				m_maze.Move(Maze::DIR_DOWN);
			}
			else
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_WALL;
			}
		}
	}
	//DOWN
	if (curr.y > 0)
	{
		MazePt next(curr.x, curr.y - 1);
		if (!m_visited[next.y * m_noGrid + next.x])
		{
			if (m_maze.Move(Maze::DIR_DOWN) == true)
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_EMPTY;
				DFS(next);
				m_maze.Move(Maze::DIR_UP);
			}
			else
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_WALL;
			}
		}
	}
	//LEFT
	if (curr.x > 0)
	{
		MazePt next(curr.x - 1, curr.y);
		if (!m_visited[next.y * m_noGrid + next.x])
		{
			if (m_maze.Move(Maze::DIR_LEFT) == true)
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_EMPTY;
				DFS(next);
				m_maze.Move(Maze::DIR_RIGHT);
			}
			else
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_WALL;
			}
		}
	}
	//RIGHT
	if (curr.x < m_noGrid - 1)
	{
		MazePt next(curr.x + 1, curr.y);
		if (!m_visited[next.y * m_noGrid + next.x])
		{
			if (m_maze.Move(Maze::DIR_RIGHT) == true)
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_EMPTY;
				DFS(next);
				m_maze.Move(Maze::DIR_LEFT);
			}
			else
			{
				m_myGrid[next.y * m_noGrid + next.x] = Maze::TILE_WALL;
			}
		}
	}
}

bool SceneTurn::BFS(MazePt start, MazePt end)
{
	std::fill(m_visited.begin(), m_visited.end(), false);
	while (!m_queue.empty())
		m_queue.pop();
	m_shortestPath.clear();
	m_queue.push(start);
	m_maze.SetNumMove(0);
	while (!m_queue.empty())
	{
		MazePt curr = m_queue.front();
		m_maze.SetCurr(curr);
		m_queue.pop();
		if (curr.x == end.x && curr.y == end.y)
		{
			while (!(curr.x == start.x && curr.y == start.y))
			{
				m_shortestPath.insert(m_shortestPath.begin(), curr);
				curr = m_previous[curr.y * m_noGrid + curr.x];
			}
			m_shortestPath.insert(m_shortestPath.begin(), curr);
			return true;
		}
		//UP
		if (curr.y < m_noGrid - 1)
		{
			MazePt next(curr.x, curr.y + 1);
			if (!m_visited[next.y * m_noGrid + next.x] && m_myGrid[next.y * m_noGrid + next.x] == Maze::TILE_EMPTY)
			{
				m_previous[next.y * m_noGrid + next.x] = curr;
				m_queue.push(next);
				m_visited[next.y * m_noGrid + next.x] = true;
			}
		}
		//DOWN
		if (curr.y > 0)
		{
			MazePt next(curr.x, curr.y - 1);
			if (!m_visited[next.y * m_noGrid + next.x] && m_myGrid[next.y * m_noGrid + next.x] == Maze::TILE_EMPTY)
			{
				m_previous[next.y * m_noGrid + next.x] = curr;
				m_queue.push(next);
				m_visited[next.y * m_noGrid + next.x] = true;
			}
		}
		//LEFT
		if (curr.x > 0)
		{
			MazePt next(curr.x - 1, curr.y);
			if (!m_visited[next.y * m_noGrid + next.x] && m_myGrid[next.y * m_noGrid + next.x] == Maze::TILE_EMPTY)
			{
				m_previous[next.y * m_noGrid + next.x] = curr;
				m_queue.push(next);
				m_visited[next.y * m_noGrid + next.x] = true;
			}
		}
		//RIGHT
		if (curr.x < m_noGrid - 1)
		{
			MazePt next(curr.x + 1, curr.y);
			if (!m_visited[next.y * m_noGrid + next.x] && m_myGrid[next.y * m_noGrid + next.x] == Maze::TILE_EMPTY)
			{
				m_previous[next.y * m_noGrid + next.x] = curr;
				m_queue.push(next);
				m_visited[next.y * m_noGrid + next.x] = true;
			}
		}
	}
	return false;
}

bool SceneTurn::BFSLimit(GameObject *go, MazePt end, int limit)
{
	std::fill(go->visited.begin(), go->visited.end(), false);
	go->stack.clear();
	go->path.clear();
	std::fill(go->previous.begin(), go->previous.end(), NULL);

	go->stack.push_back(go->curr);
	int nearestDistance = 100000;
	MazePt nearestTile = go->curr;
	MazePt curr;
	int loop = 0;
	while (!go->stack.empty() && loop < limit)
	{
		loop++;
		curr = go->stack.front();
		go->stack.erase(go->stack.begin());
		float distance = sqrtf((float)((curr.x - end.x) * (curr.x - end.x) + (curr.y - end.y) * (curr.y - end.y)));
		if (distance < nearestDistance)
		{
			nearestDistance = (int)distance;
			nearestTile = curr;
		}
		if (curr.x == end.x && curr.y == end.y)
		{
			//shorest path to end tile
			while (!(curr.x == go->curr.x && curr.y == go->curr.y))
			{
				go->path.insert(go->path.begin(), curr);
				curr = go->previous[curr.y * m_noGrid + curr.x];
			}
			go->path.insert(go->path.begin(), curr);
			return true;
		}

		//Check Up direction
		MazePt checkNext(curr.x, curr.y + 1);
		if (checkNext.y < m_noGrid
			&& !go->visited[checkNext.y * m_noGrid + checkNext.x]
			&& go->grid[checkNext.y * m_noGrid + checkNext.x] == Maze::TILE_EMPTY)
		{
			go->previous[checkNext.y * m_noGrid + checkNext.x] = curr;
			go->stack.push_back(checkNext);
			go->visited[checkNext.y * m_noGrid + checkNext.x] = true;
		}
		//Check Right
		checkNext.Set(curr.x + 1, curr.y);
		if (checkNext.x < m_noGrid
			&& !go->visited[checkNext.y * m_noGrid + checkNext.x]
			&& go->grid[checkNext.y * m_noGrid + checkNext.x] == Maze::TILE_EMPTY)
		{
			go->previous[checkNext.y * m_noGrid + checkNext.x] = curr;
			go->stack.push_back(checkNext);
			go->visited[checkNext.y * m_noGrid + checkNext.x] = true;
		}
		//Down
		checkNext.Set(curr.x, curr.y - 1);
		if (checkNext.y >= 0
			&& !go->visited[checkNext.y * m_noGrid + checkNext.x]
			&& go->grid[checkNext.y * m_noGrid + checkNext.x] == Maze::TILE_EMPTY)
		{
			go->previous[checkNext.y * m_noGrid + checkNext.x] = curr;
			go->stack.push_back(checkNext);
			go->visited[checkNext.y * m_noGrid + checkNext.x] = true;
		}
		//Left
		checkNext.Set(curr.x - 1, curr.y);
		if (checkNext.x >= 0
			&& !go->visited[checkNext.y * m_noGrid + checkNext.x]
			&& go->grid[checkNext.y * m_noGrid + checkNext.x] == Maze::TILE_EMPTY)
		{
			go->previous[checkNext.y * m_noGrid + checkNext.x] = curr;
			go->stack.push_back(checkNext);
			go->visited[checkNext.y * m_noGrid + checkNext.x] = true;
		}
	}
	//Shortest path to nearest instead
	curr = nearestTile;
	while (!(curr.x == go->curr.x && curr.y == go->curr.y))
	{
		go->path.insert(go->path.begin(), curr);
		curr = go->previous[curr.y * m_noGrid + curr.x];
	}
	go->path.insert(go->path.begin(), curr);
	return false;
}

int SceneTurn::cost_Estimate(MazePt start, MazePt end)
{
	return (abs(start.x - end.x) + abs(start.y - end.y));
}

bool SceneTurn::AStar(GameObject* go, MazePt end)
{
	if (go->grid[end.x + end.y * m_noGrid] == Maze::TILE_FOG)
		return false;

	go->stack.clear();
	std::fill(go->visited.begin(), go->visited.end(), false);
	go->path.clear();
	go->previous.resize(m_noGrid * m_noGrid);
	std::fill(go->previous.begin(), go->previous.end(), NULL);

	//The cost of getting from the start to that node
	std::vector<int> gScore;
	gScore.resize(m_noGrid * m_noGrid);
	std::fill(gScore.begin(), gScore.end(), INT_MAX);
	gScore[go->curr.x + go->curr.y * m_noGrid] = 0;

	//The cost of getting from the start to end passing that node
	std::vector<int> fScore;
	fScore.resize(m_noGrid * m_noGrid);
	std::fill(fScore.begin(), fScore.end(), INT_MAX);
	fScore[go->curr.x + go->curr.y * m_noGrid] = cost_Estimate(go->curr, end);

	go->stack.push_back(go->curr);
	int nearestDistance = INT_MAX;
	MazePt nearestTile = go->curr;
	MazePt curr;
	int loop = 0;

	while (!go->stack.empty())
	{
		int lowestFScore = INT_MAX;
		int stackIndex;
		for (unsigned int i = 0; i < go->stack.size(); ++i)
		{
			MazePt stackItem = go->stack[i];
			if (fScore[stackItem.x + stackItem.y * m_noGrid] < lowestFScore)
			{
				lowestFScore = fScore[stackItem.x + stackItem.y * m_noGrid];
				stackIndex = i;
			}				
		}

		curr = go->stack[stackIndex];

		if (curr.x == end.x && curr.y == end.y)
		{
			//shorest path to end tile
			while (!(curr.x == go->curr.x && curr.y == go->curr.y))
			{
				go->path.insert(go->path.begin(), curr);
				curr = go->previous[curr.y * m_noGrid + curr.x];
			}
			go->path.insert(go->path.begin(), curr);
			return true;
		}

		go->stack.erase(go->stack.begin() + stackIndex);
		go->visited[curr.x + curr.y * m_noGrid] = true;

		for (int dir = 0; dir < 4; ++dir)
		{
			MazePt checkNext;
			switch (dir)
			{
			case 0:
				//UP
				checkNext.Set(curr.x, curr.y + 1);
				break;
			case 1:
				//DOWN
				checkNext.Set(curr.x, curr.y - 1);
				break;
			case 2:
				//LEFT
				checkNext.Set(curr.x - 1, curr.y);
				break;
			case 3:
				//RIGHT
				checkNext.Set(curr.x + 1, curr.y);
				break;
			}
			
			if (go->visited[checkNext.y * m_noGrid + checkNext.x] == false)
			{
				int nextGScore = gScore[curr.x + curr.y * m_noGrid] + m_maze.getTileCost(go->grid[checkNext.x + checkNext.y * m_noGrid]);

				bool inStack = false;
				for (unsigned int i = 0; i < go->stack.size(); ++i)
				{
					if (go->stack[i].x == checkNext.x && go->stack[i].y == checkNext.y)
						inStack = true;
				}
				if (inStack == false)
					go->stack.push_back(checkNext);
				else if (nextGScore >= gScore[checkNext.x + checkNext.y * m_noGrid])
					continue;

				go->previous[checkNext.y * m_noGrid + checkNext.x] = curr;
				gScore[checkNext.x + checkNext.y * m_noGrid] = nextGScore;
				fScore[checkNext.x + checkNext.y * m_noGrid] = gScore[checkNext.x + checkNext.y * m_noGrid] + cost_Estimate(checkNext, end);
			}
		}		
	}

	return false;
}

bool SceneTurn::RoomVisibilityCheck(GameObject* go)
{
	for (unsigned int i = 0; i < m_maze.rooms.size(); ++i)
	{
		Room temp(go->curr.x, go->curr.y, 0, 0);
		Room temp2(m_maze.rooms[i]->x, m_maze.rooms[i]->y, (int)m_maze.rooms[i]->width - 1, (int)m_maze.rooms[i]->height - 1);
		//If player is in a room
		if (m_maze.checkOverlap(&temp, &temp2))
		{
			MazePt BtmLeftCorner(m_maze.rooms[i]->x, m_maze.rooms[i]->y);
			for (int k = -1; k < m_maze.rooms[i]->height + 1; ++k)
			{
				for (int j = -1; j < m_maze.rooms[i]->width + 1; ++j)
				{
					go->grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + k) * m_noGrid] = m_maze.m_grid[BtmLeftCorner.x + j + (BtmLeftCorner.y + k) * m_noGrid];
				}
			}

			return true;
		}
	}

	return false;
}

void SceneTurn::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('N'))
	{
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
	}

	static bool bRKeyState = false;
	if (!bRKeyState && Application::IsKeyPressed('R'))
	{
		ResetGame(m_noGrid);
		bRKeyState = true;
	}
	else if (bRKeyState && !Application::IsKeyPressed('R'))
	{
		bRKeyState = false;
	}

	//Input Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		if (posX < m_noGrid * m_gridSize && posY < m_noGrid * m_gridSize)
		{
			m_end.Set((int)(posX / m_gridSize), (int)(posY / m_gridSize));
			for (unsigned int i = 0; i < m_goList.size(); ++i)
			{
				GameObject * go = m_goList[i];
				if (go->active && go->mapReadFinished)
				{
					BFSLimit(go, m_end, 100);

					for (auto path : go->path)
					{
						std::cout << "(" << path.x << "," << path.y << ")";
					}
					std::cout << std::endl;
				}				
			}			
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

	if (player->hp > 0)
	{
		static bool bSpaceState = false;
		if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceState = true;
			GameObject *go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
			go->type = GameObject::GO_MONSTER_BULBASAUR;
			go->grid.resize(m_noGrid * m_noGrid);
			go->previous.resize(m_noGrid * m_noGrid);
			go->visited.resize(m_noGrid * m_noGrid);
			std::fill(go->grid.begin(), go->grid.end(), Maze::TILE_FOG);
			std::fill(go->visited.begin(), go->visited.end(), false);
			std::fill(go->previous.begin(), go->previous.end(), MazePt(0, 0));
			go->active = true;
			go->hp = 30;
			go->maxHp = 30;
			go->damage = 5;
			go->targetGO = NULL;
			go->sm->SetNextState("Moving");

			SceneData::GetInstance()->setMonsterCount(SceneData::GetInstance()->getMonsterCount() + 1);
			int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
			int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
			int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
			go->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
			go->pos.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
			go->target.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
			if (RoomVisibilityCheck(go) == false)
				DFSlimit(go, 4);
		}
		else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceState = false;
		}

		//Movement Keys
		if (Application::IsKeyPressed(VK_UP))
		{
			MazePt next(player->curr);
			next.y++;
			if (playerTurn && movingObjects == false)
			{
				//Check for collision with other objects
				player->objectUp = false;
				for (unsigned int j = 0; j < m_goList.size(); ++j)
				{
					if (m_goList[j]->active)
					{
						GameObject* anotherObj = m_goList[j];

						if (player->curr.x == anotherObj->curr.x && player->curr.y + 1 == anotherObj->curr.y
							&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
								anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
								anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
								anotherObj->type == GameObject::GO_PLAYER))
							player->objectUp = true;
					}
				}
				if (player->objectUp == false)
				{
					if (player->cost > 1)
					{
						player->cost--;
						playerTurn = false;
					}
					else if (player->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
					{
						std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
						std::fill(player->visited.begin(), player->visited.end(), false);
						player->curr.Set(next.x, next.y);
						player->target.Set(player->pos.x, player->pos.y + m_gridSize, player->pos.z);
						player->targetDist = (player->target - player->pos).Length();

						if (RoomVisibilityCheck(player) == false)
							DFSlimit(player, 4);

						player->cost = m_maze.getTileCost(player->grid[player->curr.x + player->curr.y * m_noGrid]);
						playerTurn = false;
					}
				}
			}
		}
		else if (Application::IsKeyPressed(VK_DOWN))
		{
			MazePt next(player->curr);
			next.y--;
			if (playerTurn && movingObjects == false)
			{
				player->objectDown = false;
				for (unsigned int j = 0; j < m_goList.size(); ++j)
				{
					if (m_goList[j]->active)
					{
						GameObject* anotherObj = m_goList[j];

						if (player->curr.x == anotherObj->curr.x && player->curr.y - 1 == anotherObj->curr.y
							&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
								anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
								anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
								anotherObj->type == GameObject::GO_PLAYER))
							player->objectDown = true;
					}
				}
				if (player->objectDown == false)
				{
					if (player->cost > 1)
					{
						player->cost--;
						playerTurn = false;
					}
					else if (player->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
					{
						std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
						std::fill(player->visited.begin(), player->visited.end(), false);
						player->curr.Set(next.x, next.y);
						player->target.Set(player->pos.x, player->pos.y - m_gridSize, player->pos.z);
						player->targetDist = (player->target - player->pos).Length();

						if (RoomVisibilityCheck(player) == false)
							DFSlimit(player, 4);

						player->cost = m_maze.getTileCost(player->grid[player->curr.x + player->curr.y * m_noGrid]);
						playerTurn = false;
					}
				}
			}
		}
		else if (Application::IsKeyPressed(VK_LEFT))
		{
			MazePt next(player->curr);
			next.x--;
			if (playerTurn && movingObjects == false)
			{
				player->objectLeft = false;
				for (unsigned int j = 0; j < m_goList.size(); ++j)
				{
					if (m_goList[j]->active)
					{
						GameObject* anotherObj = m_goList[j];

						if (player->curr.x - 1 == anotherObj->curr.x && player->curr.y == anotherObj->curr.y
							&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
								anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
								anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
								anotherObj->type == GameObject::GO_PLAYER))
							player->objectLeft = true;
					}
				}
				if (player->objectLeft == false)
				{
					if (player->cost > 1)
					{
						player->cost--;
						playerTurn = false;
					}
					else if (player->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
					{
						std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
						std::fill(player->visited.begin(), player->visited.end(), false);
						player->curr.Set(next.x, next.y);
						player->target.Set(player->pos.x - m_gridSize, player->pos.y, player->pos.z);
						player->targetDist = (player->target - player->pos).Length();

						if (RoomVisibilityCheck(player) == false)
							DFSlimit(player, 4);

						player->cost = m_maze.getTileCost(player->grid[player->curr.x + player->curr.y * m_noGrid]);
						playerTurn = false;
					}
				}
			}
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			MazePt next(player->curr);
			next.x++;
			if (playerTurn && movingObjects == false)
			{
				player->objectRight = false;
				for (unsigned int j = 0; j < m_goList.size(); ++j)
				{
					if (m_goList[j]->active)
					{
						GameObject* anotherObj = m_goList[j];

						if (player->curr.x + 1 == anotherObj->curr.x && player->curr.y == anotherObj->curr.y
							&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
								anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
								anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
								anotherObj->type == GameObject::GO_PLAYER))
							player->objectRight = true;
					}
				}
				if (player->objectRight == false)
				{
					if (player->cost > 1)
					{
						player->cost--;
						playerTurn = false;
					}
					else if (player->grid[next.x + next.y * m_noGrid] != Maze::TILE_WALL)
					{
						std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
						std::fill(player->visited.begin(), player->visited.end(), false);
						player->curr.Set(next.x, next.y);
						player->target.Set(player->pos.x + m_gridSize, player->pos.y, player->pos.z);
						player->targetDist = (player->target - player->pos).Length();

						if (RoomVisibilityCheck(player) == false)
							DFSlimit(player, 4);

						player->cost = m_maze.getTileCost(player->grid[player->curr.x + player->curr.y * m_noGrid]);
						playerTurn = false;
					}
				}
			}
		}

		//Attack Keys
		else if (Application::IsKeyPressed('W'))
		{
			MazePt next(player->curr);
			next.y++;
			if (playerTurn && movingObjects == false)
			{
				//check if any enemy is in the top tile
				for (unsigned int i = 0; i < m_goList.size(); ++i)
				{
					GameObject* go = m_goList[i];
					if (go->active && (go->type == GameObject::GO_MONSTER_BULBASAUR ||
						go->type == GameObject::GO_MONSTER_ABSOL ||
						go->type == GameObject::GO_MONSTER_FLYGON))
					{
						if (go->curr.x == next.x && go->curr.y == next.y)
						{
							int randDmg = Math::RandIntMinMax(player->damage - 3, player->damage + 3);
							go->hp -= randDmg;
							break;
						}
					}
				}
				playerTurn = false;
				player->attackDir = Maze::DIR_UP;
			}
		}
		else if (Application::IsKeyPressed('S'))
		{
			MazePt next(player->curr);
			next.y--;
			if (playerTurn && movingObjects == false)
			{
				//check if any enemy is in the top tile
				for (unsigned int i = 0; i < m_goList.size(); ++i)
				{
					GameObject* go = m_goList[i];
					if (go->active && (go->type == GameObject::GO_MONSTER_BULBASAUR ||
						go->type == GameObject::GO_MONSTER_ABSOL ||
						go->type == GameObject::GO_MONSTER_FLYGON))
					{
						if (go->curr.x == next.x && go->curr.y == next.y)
						{
							int randDmg = Math::RandIntMinMax(player->damage - 3, player->damage + 3);
							go->hp -= randDmg;
							break;
						}
					}
				}
				playerTurn = false;
				player->attackDir = Maze::DIR_DOWN;
			}
		}
		else if (Application::IsKeyPressed('A'))
		{
			MazePt next(player->curr);
			next.x--;
			if (playerTurn && movingObjects == false)
			{
				//check if any enemy is in the top tile
				for (unsigned int i = 0; i < m_goList.size(); ++i)
				{
					GameObject* go = m_goList[i];
					if (go->active && (go->type == GameObject::GO_MONSTER_BULBASAUR ||
						go->type == GameObject::GO_MONSTER_ABSOL ||
						go->type == GameObject::GO_MONSTER_FLYGON))
					{
						if (go->curr.x == next.x && go->curr.y == next.y)
						{
							int randDmg = Math::RandIntMinMax(player->damage - 3, player->damage + 3);
							go->hp -= randDmg;
							break;
						}
					}
				}
				playerTurn = false;
				player->attackDir = Maze::DIR_LEFT;
			}
		}
		else if (Application::IsKeyPressed('D'))
		{
			MazePt next(player->curr);
			next.x++;
			if (playerTurn && movingObjects == false)
			{
				//check if any enemy is in the top tile
				for (unsigned int i = 0; i < m_goList.size(); ++i)
				{
					GameObject* go = m_goList[i];
					if (go->active && (go->type == GameObject::GO_MONSTER_BULBASAUR ||
						go->type == GameObject::GO_MONSTER_ABSOL ||
						go->type == GameObject::GO_MONSTER_FLYGON))
					{
						if (go->curr.x == next.x && go->curr.y == next.y)
						{
							int randDmg = Math::RandIntMinMax(player->damage - 3, player->damage + 3);
							go->hp -= randDmg;
							break;
						}
					}
				}
				playerTurn = false;
				player->attackDir = Maze::DIR_RIGHT;
			}
		}

		//Use Oran Berry to heal
		else if (Application::IsKeyPressed('H'))
		{
			if (playerTurn && movingObjects == false)
			{
				if (player->oranBerryCount > 0)
				{
					player->oranBerryCount--;
					player->hp += Math::RandIntMinMax(45, 55);

					if (player->hp > 100)
						player->hp = 100;

					playerTurn = false;
				}
			}
		}

		static bool bMState = false;
		if (!bMState && Application::IsKeyPressed('M'))
		{
			bMState = true;
			if (toggleMap)
				toggleMap = false;
			else
				toggleMap = true;
		}
		else if (bMState && !Application::IsKeyPressed('M'))
		{
			bMState = false;
		}

		//Move AI
		if (!playerTurn && movingObjects == false)
		{
			for (unsigned int i = 0; i < m_goList.size(); ++i)
			{
				GameObject* currObj = m_goList[i];
				if (currObj->active)
				{
					if (currObj->type == GameObject::GO_MONSTER_BULBASAUR ||
						currObj->type == GameObject::GO_MONSTER_ABSOL ||
						currObj->type == GameObject::GO_MONSTER_FLYGON)
					{
						if (AStar(currObj, player->curr))
						{
							currObj->targetGO = player;
						}
						//Check for collision with other objects
						currObj->objectUp = currObj->objectDown = currObj->objectLeft = currObj->objectRight = false;
						for (unsigned int j = 0; j < m_goList.size(); ++j)
						{
							if (m_goList[j]->active)
							{
								GameObject* anotherObj = m_goList[j];
								if (currObj->curr.x + 1 == anotherObj->curr.x && currObj->curr.y == anotherObj->curr.y
									&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
										anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
										anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
										anotherObj->type == GameObject::GO_PLAYER))
									currObj->objectRight = true;

								if (currObj->curr.x - 1 == anotherObj->curr.x && currObj->curr.y == anotherObj->curr.y
									&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
										anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
										anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
										anotherObj->type == GameObject::GO_PLAYER))
									currObj->objectLeft = true;

								if (currObj->curr.x == anotherObj->curr.x && currObj->curr.y + 1 == anotherObj->curr.y
									&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
										anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
										anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
										anotherObj->type == GameObject::GO_PLAYER))
									currObj->objectUp = true;

								if (currObj->curr.x == anotherObj->curr.x && currObj->curr.y - 1 == anotherObj->curr.y
									&& (anotherObj->type == GameObject::GO_MONSTER_BULBASAUR ||
										anotherObj->type == GameObject::GO_MONSTER_ABSOL ||
										anotherObj->type == GameObject::GO_MONSTER_FLYGON ||
										anotherObj->type == GameObject::GO_PLAYER))
									currObj->objectDown = true;
							}
						}
						currObj->Update(dt);
					}
				}
			}
		}

		//Movement
		if (!playerTurn && timer < 0.3f)
			movingObjects = true;

		for (unsigned int i = 0; i < m_goList.size(); ++i)
		{
			GameObject* go = m_goList[i];
			if (go->active)
			{
				Vector3 dir = go->target - go->pos;
				if (dir.Length() < (go->targetDist / 0.3f) * dt * m_speed)
				{
					go->pos = go->target;
				}
				else if (!dir.IsZero())
				{
					dir.Normalize();
					go->pos += dir * (go->targetDist / 0.3f) * static_cast<float>(dt) * m_speed;
				}
			}
		}

		if (!playerTurn)
		{
			timer += dt * m_speed;
			if (timer >= 0.3f)
			{
				timer = 0;
				playerTurn = true;
				movingObjects = false;
				player->attackDir = Maze::DIR_NONE;

				if (player->grid[player->curr.x + player->curr.y * m_noGrid] == Maze::TILE_STAIRS && keyTaken)
				{
					stageNum++;
					playerTurn = true;
					GenerateStage(m_noGrid);
				}

				//Check if player is above any items or anything above fire tile
				if (player->grid[player->curr.x + player->curr.y * m_noGrid] == Maze::TILE_FIRE)
					player->hp -= Math::RandIntMinMax(3, 7);
				for (unsigned int i = 0; i < m_goList.size(); ++i)
				{
					GameObject* go = m_goList[i];
					if (go->active)
					{
						if (go->type == GameObject::GO_MONSTER_BULBASAUR ||
							go->type == GameObject::GO_MONSTER_ABSOL ||
							go->type == GameObject::GO_MONSTER_FLYGON)
						{
							if (go->grid[go->curr.x + go->curr.y * m_noGrid] == Maze::TILE_FIRE)
								go->hp -= Math::RandIntMinMax(3, 7);
						}
						else if (go->type == GameObject::GO_KEY)
						{
							if (player->curr.x == go->curr.x && player->curr.y == go->curr.y)
							{
								keyTaken = true;
								go->active = false;
							}
						}
						else if (go->type == GameObject::GO_ORAN_BERRY)
						{
							if (player->curr.x == go->curr.x && player->curr.y == go->curr.y)
							{
								player->oranBerryCount++;
								go->active = false;
							}
						}
					}
				}
			}
		}
	}
}

void SceneTurn::ResetGame(int noGrid)
{
	m_noGrid = noGrid;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;

	SceneData::GetInstance()->setNoGrid(m_noGrid);
	SceneData::GetInstance()->setGridSize(m_worldHeight / SceneData::GetInstance()->getNoGrid());

	m_maze.Generate(m_mazeKey, m_noGrid, m_start, m_wallLoad, 300); //Generate new maze

	SceneData::GetInstance()->mazeInfo = m_maze;

	//Clean the m_goList
	for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		if (m_goList[i]->active)
		{
			if (m_goList[i]->type == GameObject::GO_ORAN_BERRY ||
				m_goList[i]->type == GameObject::GO_MONSTER_BULBASAUR ||
				m_goList[i]->type == GameObject::GO_MONSTER_ABSOL ||
				m_goList[i]->type == GameObject::GO_MONSTER_FLYGON ||
				m_goList[i]->type == GameObject::GO_KEY)
				m_goList[i]->active = false;
		}
	}

	m_turn = 0;
	timer = 0;

	//Spawn player object
	std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
	std::fill(player->visited.begin(), player->visited.end(), false);
	std::fill(player->previous.begin(), player->previous.end(), MazePt(0, 0));

	//set go->curr to an empty tile in one of the rooms
	int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	player->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
	player->pos.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);
	player->target.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);
	player->damage = 10;
	player->hp = 100;
	player->maxHp = 100;
	player->oranBerryCount = 3;
	player->cost = 1;
	player->attackDir = Maze::DIR_NONE;

	playerTurn = false;
	if (RoomVisibilityCheck(player) == false)
		DFSlimit(player, 3);
	movingObjects = true;
	stageNum = 1;

	//Spawn the key
	keyTaken = false;
	randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	GameObject* key = FetchGO(GameObject::GO_KEY);
	key->type = GameObject::GO_KEY;
	key->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);

	//Spawn Enemies
	for (int i = 0; i < 5; ++i)
	{
		GameObject *go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
		go->type = GameObject::GO_MONSTER_BULBASAUR;
		go->grid.resize(m_noGrid * m_noGrid);
		go->previous.resize(m_noGrid * m_noGrid);
		go->visited.resize(m_noGrid * m_noGrid);
		std::fill(go->grid.begin(), go->grid.end(), Maze::TILE_FOG);
		std::fill(go->visited.begin(), go->visited.end(), false);
		std::fill(go->previous.begin(), go->previous.end(), MazePt(0, 0));
		go->active = true;
		go->hp = 30;
		go->maxHp = 30;
		go->damage = 5;
		go->targetGO = NULL;
		go->sm->SetNextState("Moving");

		SceneData::GetInstance()->setMonsterCount(SceneData::GetInstance()->getMonsterCount() + 1);
		int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
		int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
		int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
		go->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
		go->pos.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		go->target.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		if (RoomVisibilityCheck(go) == false)
			DFSlimit(go, 4);
	}

	//Spawn Oran Berries
	for (int i = 0; i < m_noGrid; ++i)
	{
		for (int j = 0; j < m_noGrid; ++j)
		{
			if (m_maze.m_grid[i + j * m_noGrid] != Maze::TILE_WALL)
			{
				if (Math::RandIntMinMax(1, 50) == 1)
				{
					bool canSpawn = true;
					//Check for any objects in that location
					for (unsigned int k = 0; k < m_goList.size(); ++k)
					{
						GameObject* go = m_goList[k];
						if (go->active)
						{
							if (go->type == GameObject::GO_KEY ||
								go->type == GameObject::GO_ORAN_BERRY)
							{
								if (go->curr.x == i && go->curr.y == j)
								{
									canSpawn = false;
								}
							}
						}
					}

					if (canSpawn)
					{
						GameObject* berry = FetchGO(GameObject::GO_ORAN_BERRY);
						berry->type = GameObject::GO_ORAN_BERRY;
						berry->curr.Set(i, j);
					}
				}
			}
		}
	}
}

void SceneTurn::GenerateStage(int noGrid)
{
	m_noGrid = noGrid;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;

	SceneData::GetInstance()->setNoGrid(m_noGrid);
	SceneData::GetInstance()->setGridSize(m_worldHeight / SceneData::GetInstance()->getNoGrid());

	m_maze.Generate(m_mazeKey, m_noGrid, m_start, m_wallLoad, 300); //Generate new maze

	SceneData::GetInstance()->mazeInfo = m_maze;

	m_turn = 0;
	timer = 0;

	//Set player spawn
	player->grid.resize(m_noGrid * m_noGrid);
	player->previous.resize(m_noGrid * m_noGrid);
	player->visited.resize(m_noGrid * m_noGrid);
	std::fill(player->grid.begin(), player->grid.end(), Maze::TILE_FOG);
	std::fill(player->visited.begin(), player->visited.end(), false);
	std::fill(player->previous.begin(), player->previous.end(), MazePt(0, 0));

	//set go->curr to an empty tile in one of the rooms
	int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	player->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
	player->pos.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);
	player->target.Set(player->curr.x * m_gridSize + m_gridOffset, player->curr.y * m_gridSize + m_gridOffset, 1);

	playerTurn = true;
	if (RoomVisibilityCheck(player) == false)
		DFSlimit(player, 3);
	movingObjects = false;

	//Spawn the key
	keyTaken = false;
	randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
	randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
	randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
	GameObject* key = FetchGO(GameObject::GO_KEY);
	key->type = GameObject::GO_KEY;
	key->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);

	//Clean the m_goList of items and enemies
	for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		if (m_goList[i]->active)
		{
			if (m_goList[i]->type == GameObject::GO_ORAN_BERRY ||
				m_goList[i]->type == GameObject::GO_MONSTER_BULBASAUR ||
				m_goList[i]->type == GameObject::GO_MONSTER_ABSOL ||
				m_goList[i]->type == GameObject::GO_MONSTER_FLYGON)
				m_goList[i]->active = false;
		}
	}

	//Spawn Enemies
	int totalMobsSpawned = 4 + stageNum;
	if (totalMobsSpawned > 8)
		totalMobsSpawned = 8;

	for (int i = 0; i < totalMobsSpawned; ++i)
	{
		GameObject *go;
		if (stageNum < 5)
		{
			go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
			go->type = GameObject::GO_MONSTER_BULBASAUR;

			go->active = true;
			go->hp = 30;
			go->maxHp = 30;
			go->damage = 5;
			
		}
		else if (stageNum < 10)
		{
			if (Math::RandIntMinMax(1, 5) == 1)
			{
				go = FetchGO(GameObject::GO_MONSTER_ABSOL);
				go->type = GameObject::GO_MONSTER_ABSOL;

				go->active = true;
				go->hp = 40;
				go->maxHp = 40;
				go->damage = 8;
			}
			else
			{
				go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
				go->type = GameObject::GO_MONSTER_BULBASAUR;

				go->active = true;
				go->hp = 30;
				go->maxHp = 30;
				go->damage = 5;
			}
		}
		else
		{
			int randInt = Math::RandIntMinMax(1, 8);
			if (randInt == 1 || randInt == 2 || randInt == 3)
			{
				go = FetchGO(GameObject::GO_MONSTER_ABSOL);
				go->type = GameObject::GO_MONSTER_ABSOL;

				go->active = true;
				go->hp = 40;
				go->maxHp = 40;
				go->damage = 8;
			}
			else if (randInt == 4 || randInt == 5)
			{
				go = FetchGO(GameObject::GO_MONSTER_FLYGON);
				go->type = GameObject::GO_MONSTER_FLYGON;

				go->active = true;
				go->hp = 45;
				go->maxHp = 45;
				go->damage = 12;
			}
			else
			{
				go = FetchGO(GameObject::GO_MONSTER_BULBASAUR);
				go->type = GameObject::GO_MONSTER_BULBASAUR;

				go->active = true;
				go->hp = 30;
				go->maxHp = 30;
				go->damage = 5;
			}
		}

		go->targetGO = NULL;
		go->sm->SetNextState("Moving");
		go->grid.resize(m_noGrid * m_noGrid);
		go->previous.resize(m_noGrid * m_noGrid);
		go->visited.resize(m_noGrid * m_noGrid);
		std::fill(go->grid.begin(), go->grid.end(), Maze::TILE_FOG);
		std::fill(go->visited.begin(), go->visited.end(), false);
		std::fill(go->previous.begin(), go->previous.end(), MazePt(0, 0));

		int randomRoom = Math::RandIntMinMax(0, m_maze.rooms.size() - 1);
		int randomX = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->width - 1);
		int randomY = Math::RandIntMinMax(0, (int)m_maze.rooms[randomRoom]->height - 1);
		go->curr.Set(m_maze.rooms[randomRoom]->x + randomX, m_maze.rooms[randomRoom]->y + randomY);
		go->pos.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		go->target.Set(go->curr.x * m_gridSize + m_gridOffset, go->curr.y * m_gridSize + m_gridOffset, 1);
		if (RoomVisibilityCheck(go) == false)
			DFSlimit(go, 4);
	}

	//Spawn Oran Berries
	for (int i = 0; i < m_noGrid; ++i)
	{
		for (int j = 0; j < m_noGrid; ++j)
		{
			if (m_maze.m_grid[i + j * m_noGrid] != Maze::TILE_WALL)
			{
				if (Math::RandIntMinMax(1, 50) == 1)
				{
					bool canSpawn = true;
					//Check for any objects in that location
					for (unsigned int k = 0; k < m_goList.size(); ++k)
					{
						GameObject* go = m_goList[k];
						if (go->active)
						{
							if (go->type == GameObject::GO_KEY ||
								go->type == GameObject::GO_ORAN_BERRY)
							{
								if (go->curr.x == i && go->curr.y == j)
								{
									canSpawn = false;
								}
							}
						}
					}

					if (canSpawn)
					{
						GameObject* berry = FetchGO(GameObject::GO_ORAN_BERRY);
						berry->type = GameObject::GO_ORAN_BERRY;
						berry->curr.Set(i, j);
					}
				}
			}
		}
	}
}

void SceneTurn::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_NONE: //Render GO_NPC
		break;
	}
}

void SceneTurn::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_WHITEQUAD], false);
	modelStack.PopMatrix();

	//Render tiles 
	for (int row = 0; row < m_noGrid; ++row)
	{
		for (int col = 0; col < m_noGrid; ++col)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_gridOffset + m_gridSize * col, m_gridOffset + m_gridSize * row, 0);
			modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
			if (toggleMap)
			{			
				switch (m_maze.m_grid[row * m_noGrid + col])
				{
				case Maze::TILE_WALL:
					RenderMesh(meshList[GEO_WALL], false);
					break;
				case Maze::TILE_FOG:
					RenderMesh(meshList[GEO_BLACKQUAD], false);
					break;
				case Maze::TILE_EMPTY:
					RenderMesh(meshList[GEO_PATH], false);
					break;
				case Maze::TILE_WATER:
					RenderMesh(meshList[GEO_WATER], false);
					break;
				case Maze::TILE_TALLGRASS:
					RenderMesh(meshList[GEO_TALL_GRASS], false);
					break;
				case Maze::TILE_FIRE:
					RenderMesh(meshList[GEO_FIRE], false);
					break;
				case Maze::TILE_STAIRS:
					if (keyTaken)
						RenderMesh(meshList[GEO_STAIRS], false);
					else
						RenderMesh(meshList[GEO_LOCKED_STAIRS], false);
					break;
				}				
			}
			else
			{
				switch (player->grid[row * m_noGrid + col])
				{
				case Maze::TILE_WALL:
					RenderMesh(meshList[GEO_WALL], false);
					break;
				case Maze::TILE_FOG:
					RenderMesh(meshList[GEO_BLACKQUAD], false);
					break;
				case Maze::TILE_EMPTY:
					RenderMesh(meshList[GEO_PATH], false);
					break;
				case Maze::TILE_WATER:
					RenderMesh(meshList[GEO_WATER], false);
					break;
				case Maze::TILE_TALLGRASS:
					RenderMesh(meshList[GEO_TALL_GRASS], false);
					break;
				case Maze::TILE_FIRE:
					RenderMesh(meshList[GEO_FIRE], false);
					break;
				case Maze::TILE_STAIRS:
					if (keyTaken)
						RenderMesh(meshList[GEO_STAIRS], false);
					else
						RenderMesh(meshList[GEO_LOCKED_STAIRS], false);
					break;
				}
			}
			modelStack.PopMatrix();
		}
	}
	
	//Render m_goList
	for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		GameObject* go = m_goList[i];

		if (go->active == true)
		{		

			if (go->type == GameObject::GO_MONSTER_BULBASAUR || go->type == GameObject::GO_MONSTER_ABSOL || go->type == GameObject::GO_MONSTER_FLYGON)
			{
				if (player->grid[go->curr.x + go->curr.y * m_noGrid] != Maze::TILE_FOG || toggleMap)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->pos.x, go->pos.y, 3);
					modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
					switch (go->type)
					{
					case GameObject::GO_MONSTER_BULBASAUR:
						RenderMesh(meshList[GEO_ENEMY_BULBASAUR], false);
						break;
					case GameObject::GO_MONSTER_ABSOL:
						RenderMesh(meshList[GEO_ENEMY_ABSOL], false);
						break;
					case GameObject::GO_MONSTER_FLYGON:
						RenderMesh(meshList[GEO_ENEMY_FLYGON], false);
						break;
					}
					modelStack.PopMatrix();

					float length = (m_gridSize - 2) / go->maxHp;
					//Red HP
					for (int j = 0; j < go->hp; ++j)
					{
						modelStack.PushMatrix();
						modelStack.Translate(go->pos.x - m_gridOffset + 1 + (j * length), go->pos.y + m_gridOffset, 5);
						modelStack.Scale(1, 1, 1);
						RenderMesh(meshList[GEO_REDQUAD], false);
						modelStack.PopMatrix();
					}

					//Outline
					for (int j = 0; j < go->maxHp; ++j)
					{
						modelStack.PushMatrix();
						modelStack.Translate(go->pos.x - m_gridOffset + 1 + (j * length), go->pos.y + m_gridOffset, 4.9f);
						modelStack.Scale(1, 1, 1);
						RenderMesh(meshList[GEO_GRAYQUAD], false);
						modelStack.PopMatrix();
					}
					for (int j = 0; j < go->maxHp; ++j)
					{
						modelStack.PushMatrix();
						modelStack.Translate(go->pos.x - m_gridOffset + 0.95f + (j * length), go->pos.y + m_gridOffset, 4.8f);
						modelStack.Scale(1.5, 1.5, 1.5);
						RenderMesh(meshList[GEO_BLACKQUAD], false);
						modelStack.PopMatrix();
					}
				}
			}
			else if (go->type == GameObject::GO_PLAYER)
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x, go->pos.y, 3);
				modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
				RenderMesh(meshList[GEO_JIRACHI], false);
				modelStack.PopMatrix();

				float length = (m_gridSize - 2) / go->maxHp;
				//Red HP
				for (int j = 0; j < go->hp; ++j)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->pos.x - m_gridOffset + 1 + (j * length), go->pos.y + m_gridOffset, 5);
					modelStack.Scale(1, 1, 1);
					RenderMesh(meshList[GEO_REDQUAD], false);
					modelStack.PopMatrix();
				}

				//Outline
				for (int j = 0; j < go->maxHp; ++j)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->pos.x - m_gridOffset + 1 + (j * length), go->pos.y + m_gridOffset, 4.9f);
					modelStack.Scale(1, 1, 1);
					RenderMesh(meshList[GEO_GRAYQUAD], false);
					modelStack.PopMatrix();
				}
				for (int j = 0; j < go->maxHp; ++j)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->pos.x - m_gridOffset + 0.95f + (j * length), go->pos.y + m_gridOffset, 4.8f);
					modelStack.Scale(1.5, 1.5, 1.5);
					RenderMesh(meshList[GEO_BLACKQUAD], false);
					modelStack.PopMatrix();
				}
			}
			else if (go->type == GameObject::GO_KEY)
			{
				if (player->grid[go->curr.x + go->curr.y * m_noGrid] != Maze::TILE_FOG || toggleMap)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->curr.x * m_gridSize + m_gridOffset, go->curr.y  * m_gridSize + m_gridOffset, 1);
					modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
					RenderMesh(meshList[GEO_KEY], false);
					modelStack.PopMatrix();
				}
			}
			else if (go->type == GameObject::GO_ORAN_BERRY)
			{
				if (player->grid[go->curr.x + go->curr.y * m_noGrid] != Maze::TILE_FOG || toggleMap)
				{
					modelStack.PushMatrix();
					modelStack.Translate(go->curr.x * m_gridSize + m_gridOffset, go->curr.y  * m_gridSize + m_gridOffset, 1);
					modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
					RenderMesh(meshList[GEO_ORAN_BERRY], false);
					modelStack.PopMatrix();
				}
			}
		}
	}

	if (player->attackDir != Maze::DIR_NONE)
	{
		modelStack.PushMatrix();
		switch (player->attackDir)
		{
		case Maze::DIR_UP:
			modelStack.Translate(player->pos.x, player->pos.y + m_gridSize, 5);
			break;
		case Maze::DIR_DOWN:
			modelStack.Translate(player->pos.x, player->pos.y - m_gridSize, 5);
			break;
		case Maze::DIR_LEFT:
			modelStack.Translate(player->pos.x - m_gridSize, player->pos.y, 5);
			break;
		case Maze::DIR_RIGHT:
			modelStack.Translate(player->pos.x + m_gridSize, player->pos.y, 5);
			break;
		}
		modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
		RenderMesh(meshList[GEO_ATTACK], false);
		modelStack.PopMatrix();
	}

	/*for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		GameObject* object = m_goList[i];
		if (object->active && object->type == GameObject::GO_NPC)
		{
			for (unsigned int j = 0; j < object->path.size(); ++j)
			{
				std::cout << "(" << object->path[j].x << "," << object->path[j].y << ")";
				MazePt pos = object->path[j];
				modelStack.PushMatrix();
				modelStack.Translate(m_gridOffset + m_gridSize * pos.x, m_gridOffset + m_gridSize * pos.y, 1);
				modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
				RenderMesh(meshList[GEO_QUEEN], false);
				modelStack.PopMatrix();
			}
			std::cout << std::endl;
		}	
	}*/

	/*for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		GameObject* object = m_goList[i];
		if (object->active && object->type == GameObject::GO_MONSTER)
		{
			for (unsigned int j = 0; j < m_noGrid; ++j)
			{
				for (unsigned int k = 0; k < m_noGrid; ++k)
				{
					if (object->grid[j + k * m_noGrid] != Maze::TILE_WALL && object->grid[j + k * m_noGrid] != Maze::TILE_FOG)
					{
						modelStack.PushMatrix();
						modelStack.Translate(m_gridOffset + m_gridSize * j, m_gridOffset + m_gridSize * k, 1);
						modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
						RenderMesh(meshList[GEO_QUEEN], false);
						modelStack.PopMatrix();
					}					
				}
			}
		}
	}*/

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	/*ss.str("");
	ss << "Turn:" << m_turn;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	ss.str("");
	ss << "Turn Maze " << m_mazeKey;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 0);*/

	ss.str("");
	ss << "HP: " << player->hp;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 50, 15);

	modelStack.PushMatrix();
	modelStack.Translate(104, 33, 1);
	modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
	RenderMesh(meshList[GEO_ORAN_BERRY], false);
	modelStack.PopMatrix();
	ss.str("");
	ss << "x " << player->oranBerryCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 54, 18);

	ss.str("");
	ss << "Stage " << stageNum;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3, 50, 25);

	if (keyTaken)
	{
		ss.str("");
		ss << "Key Secured ->";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 50, 22);
		modelStack.PushMatrix();
		modelStack.Translate(132, 39, 1);
		modelStack.Scale(m_gridSize, m_gridSize, m_gridSize);
		RenderMesh(meshList[GEO_KEY], false);
		modelStack.PopMatrix();
	}
	else
	{				
		ss.str("");
		ss << "No Key!";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 50, 22);
	}

	ss.str("");
	ss << "Find the key to unlock the exit!";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 2.5f, 50, 50);

	//Player Dead
	if (player->hp <= 0)
	{
		ss.str("");
		ss << "You Died";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 12, 7.5f, 28);

		ss.str("");
		ss << "Press R to restart game";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 5, 6.5f, 25);
	}
}

void SceneTurn::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}

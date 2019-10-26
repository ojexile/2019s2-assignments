#include "StatesMonster.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

void DFSlimit(GameObject* go, int limit);

//State Moving
StateMMoving::StateMMoving(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateMMoving::~StateMMoving()
{
}

void StateMMoving::Enter()
{
}

void StateMMoving::Update(double dt)
{
	if (m_go->hp <= 0)
	{
		m_go->active = false;
	}
	else
	{
		//Player not found
		if (m_go->targetGO == NULL)
		{
			if (m_go->cost > 1)
				m_go->cost--;
			else
			{
				std::vector<Maze::DIRECTION> availableMoves;

				if (m_go->grid[m_go->curr.x + (m_go->curr.y + 1) * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL && m_go->objectUp == false)
					availableMoves.push_back(Maze::DIR_UP);
				if (m_go->grid[m_go->curr.x + (m_go->curr.y - 1) * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL && m_go->objectDown == false)
					availableMoves.push_back(Maze::DIR_DOWN);
				if (m_go->grid[m_go->curr.x + 1 + m_go->curr.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL && m_go->objectRight == false)
					availableMoves.push_back(Maze::DIR_RIGHT);
				if (m_go->grid[m_go->curr.x - 1 + m_go->curr.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL && m_go->objectLeft == false)
					availableMoves.push_back(Maze::DIR_LEFT);

				if (availableMoves.size() > 1)
				{
					for (unsigned int i = 0; i < availableMoves.size();)
					{
						bool somethingErased = false;
						switch (availableMoves[i])
						{
						case Maze::DIR_UP:
							if (m_go->curr.x == m_go->prev.x && m_go->curr.y + 1 == m_go->prev.y)
								availableMoves.erase(availableMoves.begin() + i);
							break;
						case Maze::DIR_DOWN:
							if (m_go->curr.x == m_go->prev.x && m_go->curr.y - 1 == m_go->prev.y)
								availableMoves.erase(availableMoves.begin() + i);
							break;
						case Maze::DIR_LEFT:
							if (m_go->curr.x - 1 == m_go->prev.x && m_go->curr.y == m_go->prev.y)
								availableMoves.erase(availableMoves.begin() + i);
							break;
						case Maze::DIR_RIGHT:
							if (m_go->curr.x + 1 == m_go->prev.x && m_go->curr.y == m_go->prev.y)
								availableMoves.erase(availableMoves.begin() + i);
							break;
						}

						if (somethingErased == false)
							++i;
					}
				}

				if (availableMoves.size() != 0)
				{
					int randomMove = Math::RandIntMinMax(0, availableMoves.size() - 1);
					switch (availableMoves[randomMove])
					{
					case Maze::DIR_UP:
						m_go->prev = m_go->curr;
						m_go->curr.Set(m_go->curr.x, m_go->curr.y + 1);
						m_go->target.Set(m_go->pos.x, m_go->pos.y + SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						break;
					case Maze::DIR_DOWN:
						m_go->prev = m_go->curr;
						m_go->curr.Set(m_go->curr.x, m_go->curr.y - 1);
						m_go->target.Set(m_go->pos.x, m_go->pos.y - SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						break;
					case Maze::DIR_LEFT:
						m_go->prev = m_go->curr;
						m_go->curr.Set(m_go->curr.x - 1, m_go->curr.y);
						m_go->target.Set(m_go->pos.x - SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						break;
					case Maze::DIR_RIGHT:
						m_go->prev = m_go->curr;
						m_go->curr.Set(m_go->curr.x + 1, m_go->curr.y);
						m_go->target.Set(m_go->pos.x + SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						break;
					}

					m_go->cost = SceneData::GetInstance()->mazeInfo.getTileCost(m_go->grid[m_go->curr.x + m_go->curr.y * SceneData::GetInstance()->getNoGrid()]);
					std::fill(m_go->grid.begin(), m_go->grid.end(), Maze::TILE_FOG);
					std::fill(m_go->visited.begin(), m_go->visited.end(), false);
					DFSlimit(m_go, 4);
					m_go->targetDist = (m_go->target - m_go->pos).Length();
				}
			}
		}
		else
		{
			m_go->sm->SetNextState("Attack");
		}
	}
}

void StateMMoving::Exit()
{
}

//State Attack
StateMAttack::StateMAttack(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateMAttack::~StateMAttack()
{
}

void StateMAttack::Enter()
{
}

void StateMAttack::Update(double dt)
{
	if (m_go->hp <= 0)
	{
		m_go->active = false;
	}
	else
	{
		DFSlimit(m_go, 10000);
		if ((abs(m_go->targetGO->curr.x - m_go->curr.x) + abs(m_go->targetGO->curr.y - m_go->curr.y)) > 1)
		{
			if (m_go->cost > 1)
				m_go->cost--;
			else
			{
				m_go->prev = m_go->curr;
				if (m_go->path.size() > 1)
				{
					if (m_go->path[1].x == m_go->curr.x + 1 && m_go->objectRight == false)
					{
						m_go->target.Set(m_go->pos.x + SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						m_go->curr.Set(m_go->path[1].x, m_go->path[1].y);
					}
					else if (m_go->path[1].x == m_go->curr.x - 1 && m_go->objectLeft == false)
					{
						m_go->target.Set(m_go->pos.x - SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						m_go->curr.Set(m_go->path[1].x, m_go->path[1].y);
					}
					else if (m_go->path[1].y == m_go->curr.y + 1 && m_go->objectUp == false)
					{
						m_go->target.Set(m_go->pos.x, m_go->pos.y + SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						m_go->curr.Set(m_go->path[1].x, m_go->path[1].y);
					}
					else if (m_go->path[1].y == m_go->curr.y - 1 && m_go->objectDown == false)
					{
						m_go->target.Set(m_go->pos.x, m_go->pos.y - SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						m_go->curr.Set(m_go->path[1].x, m_go->path[1].y);
					}
				}
				else
				{
					if (m_go->path[0].x == m_go->curr.x + 1 && m_go->objectRight == false)
					{
						m_go->target.Set(m_go->pos.x + SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						m_go->curr.Set(m_go->path[0].x, m_go->path[0].y);
					}
					else if (m_go->path[0].x == m_go->curr.x - 1 && m_go->objectLeft == false)
					{
						m_go->target.Set(m_go->pos.x - SceneData::GetInstance()->getGridSize(), m_go->pos.y, m_go->pos.z);
						m_go->curr.Set(m_go->path[0].x, m_go->path[0].y);
					}
					else if (m_go->path[0].y == m_go->curr.y + 1 && m_go->objectRight == false)
					{
						m_go->target.Set(m_go->pos.x, m_go->pos.y + SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						m_go->curr.Set(m_go->path[0].x, m_go->path[0].y);
					}
					else if (m_go->path[0].y == m_go->curr.y - 1 && m_go->objectDown == false)
					{
						m_go->target.Set(m_go->pos.x, m_go->pos.y - SceneData::GetInstance()->getGridSize(), m_go->pos.z);
						m_go->curr.Set(m_go->path[0].x, m_go->path[0].y);
					}
				}

				m_go->cost = SceneData::GetInstance()->mazeInfo.getTileCost(m_go->grid[m_go->curr.x + m_go->curr.y * SceneData::GetInstance()->getNoGrid()]);
				m_go->targetDist = (m_go->target - m_go->pos).Length();
			}
		}
		else
		{
			int randDmg = Math::RandIntMinMax(m_go->damage - 3, m_go->damage + 3);
			m_go->targetGO->hp -= randDmg;
		}
	}
}

void StateMAttack::Exit()
{
}

void DFSlimit(GameObject* go, int limit)
{
	limit--;
	if (limit <= 0)
		return;

	go->visited[go->curr.y * SceneData::GetInstance()->getNoGrid() + go->curr.x] = true;
	go->grid[go->curr.y * SceneData::GetInstance()->getNoGrid() + go->curr.x] = SceneData::GetInstance()->mazeInfo.See(go->curr);

	//UP
	if (go->curr.y < SceneData::GetInstance()->getNoGrid() - 1)
	{
		MazePt next(go->curr.x, go->curr.y + 1);
		if (go->visited[next.y * SceneData::GetInstance()->getNoGrid() + next.x] == false)
		{
			go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] = SceneData::GetInstance()->mazeInfo.See(next);
			if (go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL)
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
		if (go->visited[next.y * SceneData::GetInstance()->getNoGrid() + next.x] == false)
		{
			go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] = SceneData::GetInstance()->mazeInfo.See(next);
			if (go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL)
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
		if (go->visited[next.y * SceneData::GetInstance()->getNoGrid() + next.x] == false)
		{
			go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] = SceneData::GetInstance()->mazeInfo.See(next);
			if (go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x + 1, next.y);
			}
		}
	}
	//RIGHT
	if (go->curr.x < SceneData::GetInstance()->getNoGrid() - 1)
	{
		MazePt next(go->curr.x + 1, go->curr.y);
		if (go->visited[next.y * SceneData::GetInstance()->getNoGrid() + next.x] == false)
		{
			go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] = SceneData::GetInstance()->mazeInfo.See(next);
			if (go->grid[next.x + next.y * SceneData::GetInstance()->getNoGrid()] != Maze::TILE_WALL)
			{
				go->curr = next;
				DFSlimit(go, limit);
				go->curr.Set(next.x - 1, next.y);
			}
		}
	}
}
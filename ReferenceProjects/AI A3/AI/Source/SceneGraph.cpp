#include "SceneGraph.h"
#include "StatesCreep.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::Init()
{
	SceneBase::Init();	
	PostOffice::GetInstance()->Register("SceneGraph", this);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	nodeScaleSize = 2;
	m_graphKey = 0;
	size = 4;
	//m_graph.Generate(m_graphKey, size, m_worldHeight, m_worldHeight, nodeScaleSize);
	SceneGraph::InitPath();	

	spawnTimer = 10;
	timer = spawnTimer;
	spawnCount = enemySpawnCount = 0;
	enemyStrategy = EnemyStrategy::ES_SPLIT;
	spawnDelay = 0.5f;
	spawnDelayTimer = 0;

	playerLifes = enemyLifes = 15;
	gameWon = 0;
}

void SceneGraph::SpawnTower(Vector3 position, GameObject::FACTIONS faction)
{
	GameObject* newTower = FetchGO(GameObject::GO_TOWER);
	newTower->active = true;
	newTower->type = GameObject::GO_TOWER;
	newTower->hp = newTower->maxHp = 30;
	newTower->attackSpeed = 0.5f;
	newTower->towerDestroyed = false;
	newTower->targetGO = NULL;
	newTower->range = 12;
	newTower->pos = position;
	newTower->faction = faction;
	newTower->damage = 2;
	newTower->countDown = newTower->attackSpeed;
}

void SceneGraph::SpawnMinion(int path, GameObject::FACTIONS faction)
{
	//0 = Top(BLU), 1 = Mid(BLU), 2 = Bot(BLU), 3 = Top(RED), 4 = Mid(RED), 5 = Bot(RED)
	if (faction == GameObject::FACTION_BLUE)
	{
		if (spawnCount > 0)
		{
			GameObject* go = FetchGO(GameObject::GO_NPC);
			go->type = GameObject::GO_NPC;
			go->active = true;
			go->currentPathIndex = 0;

			go->range = 3;
			go->targetGO = NULL;
			go->gPath.clear();
			AssignPath(go, path);

			go->damage = 1;
			go->maxHp = 5;
			go->hp = 5;
			go->attackSpeed = 0.4f;
			go->faction = faction;
			float posZ = go->pos.z;
			go->pos = go->gPath[0]->pos;
			go->target = go->gPath[0]->pos;
			go->pos.z = posZ;
			go->target.z = posZ;

			spawnCount--;
		}
	}
	else
	{
		if (enemySpawnCount > 0)
		{
			GameObject* go = FetchGO(GameObject::GO_NPC);
			go->type = GameObject::GO_NPC;
			go->active = true;
			go->currentPathIndex = 0;

			go->range = 3;
			go->targetGO = NULL;
			go->gPath.clear();
			AssignPath(go, path);

			go->damage = 1;
			go->maxHp = 5;
			go->hp = 5;
			go->attackSpeed = 0.4f;
			go->faction = faction;
			float posZ = go->pos.z;
			go->pos = go->gPath[0]->pos;
			go->target = go->gPath[0]->pos;
			go->pos.z = posZ;
			go->target.z = posZ;

			enemySpawnCount--;
		}
	}
}

void SceneGraph::InitPath()
{
	Node* newNode = new Node;
	newNode->pos.Set(10, 10, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(90, 90, 1);
	m_graph.AddNode(newNode);

	//Top lane
	newNode = new Node;
	newNode->pos.Set(10, 35, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(10, 60, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(20, 80, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(40, 90, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(65, 90, 1);
	m_graph.AddNode(newNode);

	//Bottom lane
	newNode = new Node;
	newNode->pos.Set(35, 10, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(60, 10, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(80, 20, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(90, 40, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(90, 65, 1);
	m_graph.AddNode(newNode);

	//Mid lane
	newNode = new Node;
	newNode->pos.Set(30, 30, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(50, 50, 1);
	m_graph.AddNode(newNode);
	newNode = new Node;
	newNode->pos.Set(70, 70, 1);
	m_graph.AddNode(newNode);


	//Edges
	//Top lane
	Edge* newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[0];
	newEdge->destination = m_graph.m_nodes[2];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[0]->Edges.push_back(newEdge);
	m_graph.m_nodes[2]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[2];
	newEdge->destination = m_graph.m_nodes[3];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[2]->Edges.push_back(newEdge);
	m_graph.m_nodes[3]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[3];
	newEdge->destination = m_graph.m_nodes[4];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[3]->Edges.push_back(newEdge);
	m_graph.m_nodes[4]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[3];
	newEdge->destination = m_graph.m_nodes[4];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[3]->Edges.push_back(newEdge);
	m_graph.m_nodes[4]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[4];
	newEdge->destination = m_graph.m_nodes[5];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[4]->Edges.push_back(newEdge);
	m_graph.m_nodes[5]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[5];
	newEdge->destination = m_graph.m_nodes[6];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[5]->Edges.push_back(newEdge);
	m_graph.m_nodes[6]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[6];
	newEdge->destination = m_graph.m_nodes[1];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[6]->Edges.push_back(newEdge);
	m_graph.m_nodes[1]->Edges.push_back(newEdge);

	//Bot lane
	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[0];
	newEdge->destination = m_graph.m_nodes[7];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[0]->Edges.push_back(newEdge);
	m_graph.m_nodes[7]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[7];
	newEdge->destination = m_graph.m_nodes[8];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[7]->Edges.push_back(newEdge);
	m_graph.m_nodes[8]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[8];
	newEdge->destination = m_graph.m_nodes[9];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[8]->Edges.push_back(newEdge);
	m_graph.m_nodes[9]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[9];
	newEdge->destination = m_graph.m_nodes[10];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[9]->Edges.push_back(newEdge);
	m_graph.m_nodes[10]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[10];
	newEdge->destination = m_graph.m_nodes[11];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[10]->Edges.push_back(newEdge);
	m_graph.m_nodes[11]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[11];
	newEdge->destination = m_graph.m_nodes[1];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[11]->Edges.push_back(newEdge);
	m_graph.m_nodes[1]->Edges.push_back(newEdge);

	//Mid lane
	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[0];
	newEdge->destination = m_graph.m_nodes[12];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[0]->Edges.push_back(newEdge);
	m_graph.m_nodes[12]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[12];
	newEdge->destination = m_graph.m_nodes[13];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[12]->Edges.push_back(newEdge);
	m_graph.m_nodes[13]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[13];
	newEdge->destination = m_graph.m_nodes[14];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[13]->Edges.push_back(newEdge);
	m_graph.m_nodes[14]->Edges.push_back(newEdge);

	newEdge = new Edge;
	newEdge->origin = m_graph.m_nodes[14];
	newEdge->destination = m_graph.m_nodes[1];
	m_graph.AddEdge(newEdge);
	m_graph.m_nodes[14]->Edges.push_back(newEdge);
	m_graph.m_nodes[1]->Edges.push_back(newEdge);

	std::vector<Node*>path;
	//Top(BLU)
	path.push_back(m_graph.m_nodes[0]);
	path.push_back(m_graph.m_nodes[2]);
	path.push_back(m_graph.m_nodes[3]);
	path.push_back(m_graph.m_nodes[4]);
	path.push_back(m_graph.m_nodes[5]);
	path.push_back(m_graph.m_nodes[6]);
	path.push_back(m_graph.m_nodes[1]);
	m_paths.push_back(path);
	path.clear();

	//Mid(BLU)
	path.push_back(m_graph.m_nodes[0]);
	path.push_back(m_graph.m_nodes[12]);
	path.push_back(m_graph.m_nodes[13]);
	path.push_back(m_graph.m_nodes[14]);
	path.push_back(m_graph.m_nodes[1]);
	m_paths.push_back(path);
	path.clear();

	//Bot(BLU)
	path.push_back(m_graph.m_nodes[0]);
	path.push_back(m_graph.m_nodes[7]);
	path.push_back(m_graph.m_nodes[8]);
	path.push_back(m_graph.m_nodes[9]);
	path.push_back(m_graph.m_nodes[10]);
	path.push_back(m_graph.m_nodes[11]);
	path.push_back(m_graph.m_nodes[1]);
	m_paths.push_back(path);
	path.clear();

	//Top(RED)
	path.push_back(m_graph.m_nodes[1]);
	path.push_back(m_graph.m_nodes[6]);
	path.push_back(m_graph.m_nodes[5]);
	path.push_back(m_graph.m_nodes[4]);
	path.push_back(m_graph.m_nodes[3]);
	path.push_back(m_graph.m_nodes[2]);
	path.push_back(m_graph.m_nodes[0]);
	m_paths.push_back(path);
	path.clear();

	//Mid(RED)
	path.push_back(m_graph.m_nodes[1]);
	path.push_back(m_graph.m_nodes[14]);
	path.push_back(m_graph.m_nodes[13]);
	path.push_back(m_graph.m_nodes[12]);
	path.push_back(m_graph.m_nodes[0]);
	m_paths.push_back(path);
	path.clear();

	//Bot(RED)
	path.push_back(m_graph.m_nodes[1]);
	path.push_back(m_graph.m_nodes[11]);
	path.push_back(m_graph.m_nodes[10]);
	path.push_back(m_graph.m_nodes[9]);
	path.push_back(m_graph.m_nodes[8]);
	path.push_back(m_graph.m_nodes[7]);
	path.push_back(m_graph.m_nodes[0]);
	m_paths.push_back(path);
	path.clear();

	//Spawn towers
	SpawnTower(m_graph.m_nodes[2]->pos, GameObject::FACTION_BLUE);
	SpawnTower(m_graph.m_nodes[3]->pos, GameObject::FACTION_BLUE);
	SpawnTower(m_graph.m_nodes[12]->pos, GameObject::FACTION_BLUE);
	SpawnTower(m_graph.m_nodes[7]->pos, GameObject::FACTION_BLUE);
	SpawnTower(m_graph.m_nodes[8]->pos, GameObject::FACTION_BLUE);
	SpawnTower(Vector3(20, 20, 0), GameObject::FACTION_BLUE);

	SpawnTower(m_graph.m_nodes[5]->pos, GameObject::FACTION_RED);
	SpawnTower(m_graph.m_nodes[6]->pos, GameObject::FACTION_RED);
	SpawnTower(m_graph.m_nodes[14]->pos, GameObject::FACTION_RED);
	SpawnTower(m_graph.m_nodes[10]->pos, GameObject::FACTION_RED);
	SpawnTower(m_graph.m_nodes[11]->pos, GameObject::FACTION_RED);
	SpawnTower(Vector3(80, 80, 0), GameObject::FACTION_RED);
}

void SceneGraph::AssignPath(GameObject *go, int pathID)
{
	//0 = Top(BLU), 1 = Mid(BLU), 2 = Bot(BLU), 3 = Top(RED), 4 = Mid(RED), 5 = Bot(RED)
	for (int i = 0; i < m_paths[pathID].size(); ++i)
	{
		go->gPath.push_back(m_paths[pathID][i]);
	}
}

bool SceneGraph::Handle(Message *message)
{
	MessageWRU *messageWRU = dynamic_cast<MessageWRU*>(message);
	if (messageWRU)
	{
		switch (messageWRU->type)
		{
		case MessageWRU::NEAREST_ENEMY:
		{
			int shortestDist = 1000;
			messageWRU->go->targetGO = NULL;
			if (messageWRU->go->faction == GameObject::FACTION_BLUE)
			{
				for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					GameObject *go = (GameObject *)*it;
					if (go->active && (go->type == GameObject::GO_NPC || go->type == GameObject::GO_TOWER) && go->faction == GameObject::FACTION_RED && go->towerDestroyed == false)
					{
						Vector3 cPos(messageWRU->go->pos.x, messageWRU->go->pos.y, 0);
						Vector3 tPos(go->pos.x, go->pos.y, 0);

						if ((tPos - cPos).Length() < shortestDist && (tPos - cPos).Length() < messageWRU->threshold)
						{
							shortestDist = (int)(tPos - cPos).Length();
							messageWRU->go->targetGO = go;
						}
					}
				}
			}
			else
			{
				for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					GameObject *go = (GameObject *)*it;
					if (go->active && (go->type == GameObject::GO_NPC || go->type == GameObject::GO_TOWER) && go->faction == GameObject::FACTION_BLUE && go->towerDestroyed == false)
					{
						Vector3 cPos(messageWRU->go->pos.x, messageWRU->go->pos.y, 0);
						Vector3 tPos(go->pos.x, go->pos.y, 0);

						if ((tPos - cPos).Length() < shortestDist && (tPos - cPos).Length() < messageWRU->threshold)
						{
							shortestDist = (int)(tPos - cPos).Length();
							messageWRU->go->targetGO = go;
						}
					}
				}
			}
			break;
		}
		}
	}

	MessageDamage *messageDMG = dynamic_cast<MessageDamage*>(message);
	if (messageDMG)
	{
		if (messageDMG->go->faction == GameObject::FACTION_BLUE)
		{
			enemyLifes--;
			if (enemyLifes <= 0)
			{
				gameWon = 1;
				m_speed = 0;
			}
		}		
		else
		{
			playerLifes--;
			if (playerLifes <= 0)
			{
				gameWon = 2;
				m_speed = 0;
			}
		}			
	}

	return false;
}

GameObject* SceneGraph::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && go->type == type)
		{
			go->active = true;
			go->pos.Set(0, 0, 10 + distance(m_goList.begin(), it) * 0.0001f);
			return go;
		}
	}

	for (unsigned i = 0; i < 5; ++i)
	{
		GameObject *go = new GameObject(type);	
		m_goList.push_back(go);		

		if (go->type == GameObject::GO_NPC)
		{
			go->sm = new StateMachine();
			go->sm->AddState(new StateCMovement("Movement", go));
			go->sm->AddState(new StateCAttack("Attack", go));
			go->sm->SetNextState("Movement");
		}
	}

	return FetchGO(type);
}

void SceneGraph::GoRandomAdjacent(GameObject *go)
{
	if (go->currNode->Edges.size() > 1)
	{
		std::vector<Edge*> availableEdges;
		for (int i = 0; i < go->currNode->Edges.size(); ++i)
		{
			if (go->currNode->Edges[i]->destination != go->prevNode && go->currNode->Edges[i]->origin != go->prevNode)
			{
				availableEdges.push_back(go->currNode->Edges[i]);
			}
		}
		
		//Random one edge to traverse
		int randomEdge = Math::RandIntMinMax(0, availableEdges.size() - 1);
		Edge* selectedEdge = availableEdges[randomEdge];

		if (selectedEdge->destination != go->currNode)
			go->gPath.push_back(selectedEdge->destination);
		else
			go->gPath.push_back(selectedEdge->origin);
	}
	else
	{
		Edge* selectedEdge = go->currNode->Edges[0];

		if (selectedEdge->destination != go->currNode)
			go->gPath.push_back(selectedEdge->destination);
		else
			go->gPath.push_back(selectedEdge->origin);
	}
}

void SceneGraph::DFSOnce(GameObject *go)
{
	go->gStack.push_back(go->currNode);
	go->visited[go->currNode->id] = true;

	for (int i = 0; i < go->currNode->Edges.size(); ++i)
	{
		Edge* currEdge = go->currNode->Edges[i];
		if (go->visited[currEdge->destination->id] == false)
		{
			go->currNode = currEdge->destination;
			return;
		}			
		else if (go->visited[currEdge->origin->id] == false)
		{
			go->currNode = currEdge->origin;
			return;
		}		
	}

	go->gStack.pop_back();

	if (!go->gStack.empty())
	{
		go->currNode = go->gStack.back();
		go->gStack.pop_back();
		return;
	}
}

void SceneGraph::Update(double dt)
{
	SceneBase::Update(dt * m_speed);

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
	if (Application::IsKeyPressed('M'))
	{
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
	}
	if (Application::IsKeyPressed('R'))
	{
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

	static bool bQState = false;
	if (!bQState && Application::IsKeyPressed('Q'))
	{
		bQState = true;
		SpawnMinion(0, GameObject::FACTION_BLUE);
	}
	else if (bQState && !Application::IsKeyPressed('Q'))
	{
		bQState = false;
	}

	static bool bWState = false;
	if (!bWState && Application::IsKeyPressed('W'))
	{
		bWState = true;
		SpawnMinion(1, GameObject::FACTION_BLUE);
	}
	else if (bWState && !Application::IsKeyPressed('W'))
	{
		bWState = false;
	}

	static bool bEState = false;
	if (!bEState && Application::IsKeyPressed('E'))
	{
		bEState = true;
		SpawnMinion(2, GameObject::FACTION_BLUE);
	}
	else if (bEState && !Application::IsKeyPressed('E'))
	{
		bEState = false;
	}

	static bool bFState = false;
	if (!bFState && Application::IsKeyPressed('F'))
	{
		bFState = true;
		enemyStrategy = EnemyStrategy::ES_SPLIT;
	}
	else if (bFState && !Application::IsKeyPressed('F'))
	{
		bFState = false;
	}

	static bool bGtate = false;
	if (!bGtate && Application::IsKeyPressed('G'))
	{
		bGtate = true;
		enemyStrategy = EnemyStrategy::ES_RUSH;
	}
	else if (bGtate && !Application::IsKeyPressed('G'))
	{
		bGtate = false;
	}

	static bool bRtate = false;
	if (!bRtate && Application::IsKeyPressed('R'))
	{
		bRtate = true;
		for (int i = 0; i < m_goList.size(); ++i)
		{
			if (m_goList[i]->active)
				m_goList[i]->active = false;
		}

		SceneGraph::InitPath();

		spawnTimer = 10;
		timer = spawnTimer;
		spawnCount = enemySpawnCount = 0;
		spawnDelay = 0.5f;
		spawnDelayTimer = 0;

		playerLifes = enemyLifes = 15;
		gameWon = 0;
		m_speed = 1;
	}
	else if (bRtate && !Application::IsKeyPressed('R'))
	{
		bRtate = false;
	}

	timer -= dt * m_speed;
	if (timer <= 0)
	{
		spawnCount = enemySpawnCount = 5;
		timer = spawnTimer;
	}

	//EnemyAI
	spawnDelayTimer -= dt * m_speed;
	if (enemySpawnCount > 0 && spawnDelayTimer <= 0)
	{
		switch (enemyStrategy)
		{
		case EnemyStrategy::ES_SPLIT:
			//2 1 2
			if (enemySpawnCount >= 3)
			{
				SpawnMinion(3, GameObject::FACTION_RED);
				SpawnMinion(4, GameObject::FACTION_RED);
				SpawnMinion(5, GameObject::FACTION_RED);
			}
			else
			{
				SpawnMinion(3, GameObject::FACTION_RED);
				SpawnMinion(5, GameObject::FACTION_RED);
			}
			break;
		case EnemyStrategy::ES_RUSH:
			//RUSH MID
			SpawnMinion(4, GameObject::FACTION_RED);
			break;
		}

		spawnDelayTimer = spawnDelay;
	}

	static const float NPC_VELOCITY = 10.f;
	for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		GameObject* go = m_goList[i];
		if (go->active && go->type == GameObject::GO_NPC)
		{						
			go->Update(dt  * m_speed);

			Vector3 dir;
			try 
			{
				dir = (go->target - go->pos).Normalized();
			}
			catch (DivideByZero)
			{
				go->target.x -= 0.01f;
				dir = (go->target - go->pos).Normalized();
			}
			go->pos.x += dir.x * NPC_VELOCITY * m_speed * static_cast<float>(dt) * go->moveSpeed;	
			go->pos.y += dir.y * NPC_VELOCITY * m_speed * static_cast<float>(dt) * go->moveSpeed;
		}
		else if (go->active && go->type == GameObject::GO_TOWER)
		{
			if (go->towerDestroyed == false)
			{
				if (go->hp <= 0)
					go->towerDestroyed = true;

				if (go->targetGO && go->targetGO->active && go->targetGO->hp > 0)
				{
					if (go->countDown <= 0)
					{
						go->targetGO->hp -= go->damage;
						go->countDown = go->attackSpeed;
					}
				}
				else
				{
					MessageWRU *msg = new MessageWRU(go, MessageWRU::NEAREST_ENEMY, go->range);
					Handle(msg);
				}

				go->countDown -= dt * m_speed;
			}
		}
	}
}



void SceneGraph::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_NPC:
		{
			Vector3 dir;
			try
			{
				dir = (go->target - go->pos).Normalized();
			}
			catch (DivideByZero)
			{
				go->target.y += 0.01f;
				dir = (go->target - go->pos).Normalized();
			}
			float rotation = Math::RadianToDegree(atan2f(dir.y, dir.x));
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(rotation - 90, 0, 0, 1);
			modelStack.Scale(3, 3, 1);
			if (go->faction == GameObject::FACTION_BLUE)
				RenderMesh(meshList[GEO_ALLY], false);
			else
				RenderMesh(meshList[GEO_ENEMY], false);
			modelStack.PopMatrix();
			
			for (int i = 0; i < go->hp; ++i)
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x + i - (go->maxHp * 0.5f), go->pos.y + 3, go->pos.z);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_REDQUAD], false);
				modelStack.PopMatrix();
			}

			for (int i = 0; i < go->maxHp; ++i)
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x + i - (go->maxHp * 0.5f), go->pos.y + 3, go->pos.z);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_BLACKQUAD], false);
				modelStack.PopMatrix();
			}
			break;
		}	
	case GameObject::GO_TOWER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(3, 3, 1);
		if (go->faction == GameObject::FACTION_BLUE)
			RenderMesh(meshList[GEO_TOWER_ALLY], false);
		else
			RenderMesh(meshList[GEO_TOWER_ENEMY], false);
		modelStack.PopMatrix();

		for (int i = 0; i < go->hp; ++i)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x + i * 0.5f - (go->maxHp * 0.25f), go->pos.y + 4, go->pos.z);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_REDQUAD], false);
			modelStack.PopMatrix();
		}

		for (int i = 0; i < go->maxHp; ++i)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x + i * 0.5f - (go->maxHp * 0.25f), go->pos.y + 4, go->pos.z);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_BLACKQUAD], false);
			modelStack.PopMatrix();
		}
		break;
	}
}

void SceneGraph::RenderGraph()
{
	for (int i = 0; i < m_graph.m_nodes.size(); ++i)
	{
		Node* currNode = m_graph.m_nodes[i];

		modelStack.PushMatrix();
		modelStack.Translate(currNode->pos.x, currNode->pos.y, 1.f);
		modelStack.Scale(nodeScaleSize, nodeScaleSize, nodeScaleSize);
		RenderMesh(meshList[GEO_SPHERE], false);
		std::ostringstream ss;
		ss << currNode->id;
		RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0));
		modelStack.PopMatrix();
	}

	for (int i = 0; i < m_graph.m_edges.size(); ++i)
	{
		Edge* currEdge = m_graph.m_edges[i];

		Vector3 edgeDir = (currEdge->destination->pos - currEdge->origin->pos).Normalized();
		Vector3 pos = currEdge->origin->pos + (currEdge->destination->pos - currEdge->origin->pos) * 0.5f;
		float rotation = Math::RadianToDegree(atan2f(edgeDir.y, edgeDir.x));
		modelStack.PushMatrix();
		modelStack.Translate(pos.x, pos.y, 1.f);
		modelStack.Rotate(rotation, 0, 0, 1);
		modelStack.Scale(currEdge->cost, 1, 1);
		RenderMesh(meshList[GEO_LINE], false);
		modelStack.PopMatrix();	

		modelStack.PushMatrix();
		modelStack.Translate(pos.x, pos.y, 1.f);
		modelStack.Scale(4, 4, 1);
		std::ostringstream ss;
		ss << currEdge->cost;
		RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 1, 1));
		modelStack.PopMatrix();		
	}
}

void SceneGraph::Render()
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

	RenderGraph();

	for (auto go : m_goList)
	if(go->active)
		RenderGO(go);

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	ss.str("");
	ss << "Graph " << 0;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 0);

	ss.str("");
	ss << "Next Wave in " << timer;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	ss.str("");
	ss << "Minions Spawnable " << spawnCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 12);

	ss.str("");
	ss << "PlayerHP: " << playerLifes;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 50, 18);

	ss.str("");
	ss << "EnemyHP: " << enemyLifes;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3, 50, 21);

	if (gameWon == 1)
	{
		ss.str("");
		ss << "Game Won! Press r to Reset Game";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 5, 10, 30);
	}
	else if (gameWon == 2)
	{
		ss.str("");
		ss << "Game Lost! Press r to Reset Game";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 5, 10, 30);
	}
}

void SceneGraph::Exit()
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

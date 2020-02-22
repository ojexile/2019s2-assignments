#ifndef SCENE_BIRD_H
#define SCENE_BIRD_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

struct AABB
{
	float width;
	float height;
	//Vector3 position;
	Vector3 position;
	Vector3 points[4];
	//[0] --> [1]
	//[2] --> [3]

	AABB()
	{
		Set(0, 0, 0);
	}

	void Set(float w, float h, Vector3 pos)
	{
		position = pos;

		width = w;
		height = h;

		points[0].x = pos.x - w / 2;
		points[0].y = pos.y + h / 2;

		points[1].x = pos.x + w / 2;
		points[1].y = pos.y + h / 2;

		points[2].x = pos.x - w / 2;
		points[2].y = pos.y - h / 2;

		points[3].x = pos.x + w / 2;
		points[3].y = pos.y - h / 2;
	}

	void Update(Vector3 value)
	{
		position += value;
		for (int i = 0; i < 4; ++i)
		{
			points[i] += value;
		}
	}
};

struct Pipes
{
	public:
		float m_gap;
		GameObject m_top;
		GameObject m_bottom;
		Vector3 m_position;
		Vector3 m_collisionCheck;

		//Is it active
		bool m_active;

		//AABB
		AABB m_aabbTop;
		AABB m_aabbBot;

		//Constructor
		Pipes()
		{

		}
};


class SceneFlappyBird : public SceneBase
{
public:
	SceneFlappyBird();
	~SceneFlappyBird();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	Pipes* FetchPipe();
	void Restart();
	void UpdateCharacter(GameObject* go, double dt);
	void RenderGO(GameObject *go);
	void RenderPipes();
	void UpdatePipes(double dt);
	Pipes* GetNextPipe(float x);

	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);
	float Sigmoid(float x);
	float Derivative(float x);
	float FeedNN(GameObject* go, std::vector<float> &inputList);
protected:

	std::vector<GameObject *> m_goList;
	std::vector<Pipes* > m_pipesList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;

	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;
	
	float m_jumpForce;
	float m_characterRadius;

	float m_pipeScaleX;
	float m_pipeScaleY;
	float m_pipeGapMin;
	float m_pipeGapMax;

	float m_gravity;
	float m_gameSpeed;

	float m_spawnTimer;
	float m_spawnTime;
	float m_spawnReduceTime;
	float m_spawnReducerTimer;

	int m_highScore;
	int m_score;
	int generation;

	NeuralNode addThis;
};

#endif
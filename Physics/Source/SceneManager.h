#pragma once
#include "Scene.h"
#include "TestScene.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	static Scene* m_CurrentScene;
public:
	SceneManager();
	~SceneManager();

	void ChangeScene(Scene* scene);
	Scene* GetScene();
	void DeleteScene();
};

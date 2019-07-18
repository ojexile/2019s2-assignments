#pragma once
#include "Scene.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	Scene* m_CurrentScene;
public:
	SceneManager();
	virtual ~SceneManager();

	void ChangeScene(Scene* scene);
	Scene* GetScene();
	void DeleteScene();
};

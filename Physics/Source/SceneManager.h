#pragma once
#include "Scene.h"
#include "TestScene.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	Scene* m_CurrentScene;
	Scene* m_TempScene;
	bool m_bSceneChanged;
public:
	SceneManager();
	virtual ~SceneManager();

	void ChangeScene(Scene* scene);
	Scene* GetScene();
	void DeleteScene();
	bool IsSceneChanged();
	void SwapScene();
};

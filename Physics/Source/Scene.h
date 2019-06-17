#pragma once
#include "GameObjectManager.h"
#include "Camera.h"
class Scene
{
private:
	virtual void InitCamera() = 0;
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	GameObject* GetCameraGameObject();
	Camera* GetCamera();
	GameObjectManager& GetGameObjectManager();
protected:
	GameObjectManager m_GameObjectManager;
	GameObject* m_CameraGO;
	Camera* m_Camera;
};

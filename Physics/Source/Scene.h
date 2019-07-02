#pragma once
#include "GameObjectManager.h"
#include "Camera.h"
#include "CameraComponent.h"

#define TRANSFORM GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	GameObject* GetCameraGameObject();
	Camera* GetCamera();
	GameObjectManager* GetGameObjectManager();
protected:
	GameObjectManager m_GameObjectManager;
	GameObject* m_CameraGO;
	Camera* m_Camera;
};

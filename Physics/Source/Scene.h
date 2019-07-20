#pragma once
#include "GameObjectManager.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "LightManager.h"

#define TRANSFORM GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	GameObject* GetCameraGameObject();
	Camera* GetCamera();
	GameObjectManager* GetGameObjectManager();
	LightManager* GetLightManager();
	void SetCursorEnabled(bool);
protected:
	GameObjectManager m_GameObjectManager;
	LightManager m_LightManager;
	GameObject* m_CameraGO;
	Camera* m_Camera;
};

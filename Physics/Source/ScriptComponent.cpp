#include "ScriptComponent.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "GenericSubject.h"
ScriptComponent::ScriptComponent()
{
}

ScriptComponent::~ScriptComponent()
{
}

void ScriptComponent::Update(double dt)
{
	return;
}

void ScriptComponent::Collide(GameObject*)
{
}
Camera*  ScriptComponent::GetCamera()
{
	return SceneManager::GetInstance()->GetScene()->GetCamera();
}
GameObject*  ScriptComponent::GetCameraGO()
{
	return SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
}
LightManager* ScriptComponent::GetLightManager()
{
	return SceneManager::GetInstance()->GetScene()->GetLightManager();
}
TransformComponent* ScriptComponent::GetTransform()
{
	return GetComponent<TransformComponent>();
}
void ScriptComponent::Notify(std::string msg)
{
	GenericSubject::GetInstance()->NotifySubject(this, msg);
}
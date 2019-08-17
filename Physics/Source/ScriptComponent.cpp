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

void ScriptComponent::Destroy(GameObject* go)
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->GetScene()->GetGameObjectManager()->QueueDestroy(go);
}

void ScriptComponent::DestroySelf()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->GetScene()->GetGameObjectManager()->QueueDestroyFromComponent(this);
}
GameObject* ScriptComponent::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, vScal, vRot, fAngle, sLayer);
}
GameObject* ScriptComponent::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer, bool isChild) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, vScal, sLayer, isChild);
}
GameObject* ScriptComponent::Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, sLayer);
}
GameObject* ScriptComponent::Instantiate(const GameObject* goRef, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, sLayer);
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
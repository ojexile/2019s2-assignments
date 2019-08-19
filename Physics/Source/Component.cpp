#include "Component.h"
#include "SceneManager.h"
#include "Vector3.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
Component::Component()
{
}
Component::~Component()
{
}

void Component::Destroy(GameObject* go)
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->GetScene()->GetGameObjectManager()->QueueDestroy(go);
}

void Component::DestroySelf()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->GetScene()->GetGameObjectManager()->QueueDestroyFromComponent(this);
}
GameObject* Component::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, vScal, vRot, fAngle, sLayer);
}
GameObject* Component::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer, bool isChild) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, vScal, sLayer, isChild);
}
GameObject* Component::Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, pos, sLayer);
}
GameObject* Component::Instantiate(const GameObject* goRef, std::string sLayer) const
{
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	return GOM->Instantiate(goRef, sLayer);
}
Vector3 Component::GetPosition()
{
	return GetComponent<TransformComponent>()->GetPosition();
}
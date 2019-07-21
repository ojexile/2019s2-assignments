#include "ScriptComponent.h"
#include "SceneManager.h"
#include "DataContainer.h"
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
	sceneManager->GetScene()->GetGameObjectManager()->Destroy(go);
}

void ScriptComponent::DestroySelf()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->GetScene()->GetGameObjectManager()->DestroySelf(this);
}
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go, sLayer);
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			Trans->SetRotation(fAngle, (int)vRot.x, (int)vRot.y, (int)vRot.z);
			Trans->SetScale(vScal.x, vScal.y, vScal.z);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			Trans->SetScale(vScal.x, vScal.y, vScal.z);
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, std::string sLayer)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* ScriptComponent::Instantiate(GameObject* goRef, std::string sLayer)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
TransformComponent*  ScriptComponent::GetTransform()
{
	return GetComponent<TransformComponent>();
}
Vector3 ScriptComponent::GetPosition()
{
	GetTransform()->GetPosition();
}
Camera*  ScriptComponent::GetCamera()
{
	SceneManager::GetInstance()->GetScene()->GetCamera();
}
GameObject*  ScriptComponent::GetCameraGO()
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
}
LightManager* ScriptComponent::GetLightManager()
{
	SceneManager::GetInstance()->GetScene()->GetLightManager();
}
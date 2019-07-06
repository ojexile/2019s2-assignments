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
void ScriptComponent::Start()
{
	return;
}
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go);
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
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal)
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
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go);
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
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos)
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
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go);
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
GameObject* ScriptComponent::Instantiate(GameObject* goRef)
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go);
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
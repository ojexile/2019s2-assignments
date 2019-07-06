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
GameObject* ScriptComponent::Instantiate(GameObject* goRef, Vector3 pos, Vector3 vRot, Vector3 vScal)
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
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
GameObject* ScriptComponent::Instantiate(std::string sName, Vector3 pos, Vector3 vRot, Vector3 vScal)
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	DataContainer* dataContainer = DataContainer::GetInstance();

	// TODO change to pooling
	if (dataContainer->GetGameObject(sName))
	{
		GameObject* go = dataContainer->GetGameObject(sName)->Clone();
		sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(go);
		return go;
	}
	DEFAULT_LOG("Instantiate failed.");
	return nullptr;
}
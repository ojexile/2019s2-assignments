#include "ComponentBase.h"
#include "SceneManager.h"
#include "DataContainer.h"
ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Init(std::vector<ComponentBase*>* refList)
{
	m_vec_RefList = refList;
}
void ComponentBase::Instantiate(std::string sName, Vector3 pos, Vector3 vRot, Vector3 vScal)
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	DataContainer* dataContainer = DataContainer::GetInstance();
	// TODO change to pooling
	if (dataContainer->GetGameObject(sName))
		sceneManager->GetScene()->GetGameObjectManager()->AddGameObject(dataContainer->GetGameObject(sName));
}
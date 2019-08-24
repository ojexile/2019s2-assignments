#include "AudioObserver.h"
#include "AudioManager.h"
#include "ComponentMacros.h"
AudioObserver::AudioObserver()
{
}

AudioObserver::~AudioObserver()
{
}

void AudioObserver::Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg == "Jump")
	{
		AudioManager::GetInstance()->Play3D("boing.wav", com->TRANS->GetPosition());
	}
	if (msg == "Walk")
	{
		AudioManager::GetInstance()->Play3DWithCooldown("walk.wav", com->TRANS->GetPosition(), 0.4f);
	}
}
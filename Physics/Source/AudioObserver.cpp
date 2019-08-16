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
	if (msg == "susu")
	{
		AudioManager::GetInstance()->Play3D("susu.wav",com->TRANS->GetPosition());
		CHENG_LOG("susu");
	}
}
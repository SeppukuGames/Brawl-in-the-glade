#include "AudioComponent.h"
#include <string>
#include "AudioManager.h"
#include <iostream>
using namespace std;

AudioComponent::AudioComponent(char * audioName, bool isLooped, bool playOnAwake) :
audioName(audioName), isLooped(isLooped), playOnAwake(playOnAwake)
{
}

AudioComponent::~AudioComponent(){
}

void AudioComponent::Start(){
	if (playOnAwake)
		Play();
}

void AudioComponent::Play(){
	AudioManager::GetInstance()->GetSoundEngine()->play2D(audioName, isLooped);
}


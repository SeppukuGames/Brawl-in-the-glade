#include "AudioComponent.h"
#include <string>
#include "AudioManager.h"
#include <iostream>
using namespace std;

AudioComponent::AudioComponent(char * audioName, bool isLooped)
{
	this->audioName = audioName;
	this->isLooped = isLooped;
}

AudioComponent::~AudioComponent(){
}

void AudioComponent::Start(){
	AudioManager::GetInstance()->GetSoundEngine()->play2D(audioName, isLooped);
}


#include "AudioComponent.h"
#include "AudioManager.h"
#include <ik_irrKlangTypes.h>

using namespace std;

AudioComponent::AudioComponent(char * audioName, bool isLooped, bool playOnAwake) :
audioName(audioName), isLooped(isLooped), playOnAwake(playOnAwake)
{
	//Guardamos la referencia del motor de sonido
	soundEngine = AudioManager::GetInstance()->GetSoundEngine();
}

AudioComponent::~AudioComponent(){
	soundEngine->removeSoundSource(audioName);
	//sound->drop();
}

void AudioComponent::Start(){
	AudioManager::GetInstance()->AddSound(this);

	//No reproduce el sonido, solamente es para guardar la referencia al sonido
	sound = soundEngine->play2D(audioName, isLooped, true, true);

	//Si la música suena desde el principio, se reproduce
	if (playOnAwake)
		Play();
}

//Empieza a reproducir el sonido
void AudioComponent::Play(){
	sound->setIsPaused(false);
}

//Pausa el sonido
void AudioComponent::Pause(){
	sound->setIsPaused(true);
}

//Para el sonido
void AudioComponent::Stop(){
	sound->stop();
}

//Ajusta el volumen para cada sonido concreto
void AudioComponent::SetVolume(irrklang::ik_f32 volume){
	sound->setVolume(volume);
}



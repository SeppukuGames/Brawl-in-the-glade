#include "AudioManager.h"
#include "Error.h"

using namespace irrklang;

#pragma region Singleton  

/* Null, because instance will be initialized on demand. */
AudioManager* AudioManager::instance = 0;

AudioManager* AudioManager::GetInstance()
{
	if (instance == 0)
		instance = new AudioManager();

	return instance;
}

void AudioManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

AudioManager::AudioManager() :
soundEngine(0)
{
}

AudioManager::~AudioManager()
{
	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().
	soundEngine->drop();
}

void AudioManager::InitSoundEngine(void){

	// Inicializa el motor de audio con parámetros por defecto
	soundEngine = createIrrKlangDevice();

	if (soundEngine == nullptr)
	{
		Error errorE("Error al inicializar el motor de audio\n");
		throw errorE;

	}
}

//Reanuda todos los sonidos
void AudioManager::Resume(){
	while (!soundsPaused.empty()){
		soundsPaused.back()->Play();
		soundsPaused.pop();
	}
}

//Pausa todos los sonidos
void AudioManager::Pause(){
	
	for (size_t i = 0; i < sounds.size(); i++){
		//Caso en el que la canción esta pausada, para no reanudarla al quitar la pausa
		if (!sounds[i]->GetIsPaused())
		{
			soundsPaused.push(sounds[i]);
			sounds[i]->Pause();
		}
	}
}

//Establece el volumen global
void AudioManager::SetGlobalVolume(irrklang::ik_f32 volume){
	soundEngine->setSoundVolume(volume);
}


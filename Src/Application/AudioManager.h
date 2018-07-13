#ifndef __AudioManager_h_
#define __AudioManager_h_

#include "irrKlang.h"
#include "AudioComponent.h"
#include <queue>

class AudioManager
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static AudioManager *instance;

public:
	/* Static access method. */
	static AudioManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	irrklang::ISoundEngine* soundEngine;	//Manager de irrklang
	queue<AudioComponent*> soundsPaused;		//Sonidos que se estaban reproduciendo y hay que reanudar
	std::vector<AudioComponent*> sounds;		//Sonidos cargados

public:
	void InitSoundEngine(void);

	void Resume();	//Reanuda todos los sonidos
	void Pause();	//Pausa todos los sonidos
	void SetGlobalVolume(irrklang::ik_f32 volume);	//Establece el volumen global

	//Getters
	inline irrklang::ISoundEngine* GetSoundEngine(){ return soundEngine; };
	inline std::vector<AudioComponent*>GetSounds(){ return sounds; }; //Devuelve el vector de canciones de la escena
	inline void AddSound(AudioComponent* audioComponent){ sounds.push_back(audioComponent); };

private:
	/* Private constructor to prevent instancing. */
	AudioManager();
	~AudioManager();

};
#endif // #ifndef __AudioManager_h_

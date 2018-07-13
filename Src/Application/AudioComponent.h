#ifndef __AudioComponent_h_
#define __AudioComponent_h_
#include "Component.h"
#include <irrKlang.h>

using namespace std;

class AudioComponent : public Component{

#pragma region Attributes  
private:
	//Atributos de construcción del componente
	char * audioName;
	bool isLooped;
	bool playOnAwake;

	irrklang::ISound * sound;				//Sonido creado
	irrklang::ISoundEngine *soundEngine;	//Referencia al motor de sonido

#pragma endregion Attributes

#pragma region Methods  

public:
	AudioComponent(char * audioName, bool isLooped, bool playOnAwake);
	~AudioComponent();

	void Start();

	//Métodos públicos para poder modificar parámetros del audio
	void Play();	//Empieza a reproducir el sonido
	void Pause();	//Pausa el sonido(TODO: FUNCIONAR)
	void Stop();	//Para el sonido

	void SetVolume(irrklang::ik_f32 volume);	//Establece el volumen propio del sonido

	//Getters de atributos
	inline irrklang::ISound* GetSound(){ return sound; };
	inline char * GetAudioName(){ return audioName; };
	inline bool GetIsLooped(){ return isLooped; };
	inline bool GetIsPaused(){ return sound->getIsPaused(); };

#pragma endregion Methods

};

#endif /* __AudioComponent_h_ */
#ifndef __AudioManager_h_
#define __AudioManager_h_

#include "irrKlang.h"

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

	irrklang::ISoundEngine* soundEngine;


public:
	void InitSoundEngine(void);
	inline irrklang::ISoundEngine* GetSoundEngine(){ return soundEngine; };

private:
	/* Private constructor to prevent instancing. */
	AudioManager();
	~AudioManager();


};
#endif // #ifndef __AudioManager_h_

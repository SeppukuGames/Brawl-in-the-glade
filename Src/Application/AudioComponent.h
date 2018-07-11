#ifndef __AudioComponent_h_
#define __AudioComponent_h_
#include <string>
#include "Component.h"
#include <irrKlang.h>

using namespace std;

class AudioComponent : public Component{

#pragma region Attributes  
private:
	char * audioName;
	bool isLooped;
	bool playOnAwake;

#pragma endregion Attributes

#pragma region Methods  

public:
	AudioComponent(char * audioName, bool isLooped, bool playOnAwake);
	~AudioComponent();

	void Start();
	void Play();
#pragma endregion Methods

};

#endif /* __AudioComponent_h_ */
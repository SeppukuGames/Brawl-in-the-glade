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

#pragma endregion Attributes

#pragma region Methods  

public:
	AudioComponent(char * audioName, bool isLooped);
	~AudioComponent();

	void Start();



#pragma endregion Methods

};

#endif /* __AudioComponent_h_ */
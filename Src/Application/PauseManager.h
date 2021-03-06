#ifndef __PauseManager_h_
#define __PauseManager_h_

#include "Component.h"
#include "Ogre.h"

class PauseManager : public Component{

#pragma region Attributes
private:
	Ogre::Timer* timer; //Variable para controlar tiempo que ha transcurrido

#pragma endregion Attributes

#pragma region Methods

public:
	PauseManager();
	virtual ~PauseManager(){};

	virtual void Start();
	virtual void Update(double elapsed);

#pragma endregion Methods

};

#endif /* __PauseManager_h_ */
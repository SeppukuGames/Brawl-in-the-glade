#ifndef __GameManager_h_
#define __GameManager_h_

#include "Component.h"
#include "Ogre.h"

class GameManager : public Component{

#pragma region Attributes  
private:
	Ogre::Timer* timer;

#pragma endregion Attributes

#pragma region Methods  

public:
	GameManager(){};
	virtual ~GameManager(){};

	virtual void Start();
	virtual void Update(double elapsed);


#pragma endregion Methods

};

#endif /* __GameManager_h_ */
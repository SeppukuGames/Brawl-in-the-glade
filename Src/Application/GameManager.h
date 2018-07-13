#ifndef __GameManager_h_
#define __GameManager_h_

#include "Component.h"
#include "Ogre.h"

//Clase encargada de gestionar el estado de la escena
class GameManager : public Component{

#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static GameManager *instance;

public:
	/* Static access method. */
	static GameManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

#pragma region Attributes  
private:
	Ogre::Timer* timer;

#pragma endregion Attributes

#pragma region Methods  

public:
	virtual void Start();
	virtual void Update(double elapsed);

	virtual ~GameManager(){};
private:
	GameManager(){};


#pragma endregion Methods

};

#endif /* __GameManager_h_ */
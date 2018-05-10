#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include "TutorialApplication.h"
#include <OIS.h>


class KeyInputComponent : public Component, public OIS::KeyListener{
public:
//----------------------M�TODOS---------------------------
	//Seguramente haya que pasarle un puntero al GameManager
	KeyInputComponent() : Component()
	{
		TutorialApplication::getInstance()->registerKeyInputObserver(this);
	};

	virtual ~KeyInputComponent(){};
	
//----------------------M�TODOS---------------------------

};

#endif /* KEYINPUTCOMPONENT_H_*/
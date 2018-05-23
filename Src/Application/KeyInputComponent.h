#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include "TutorialApplication.h"
#include <OIS.h>

class KeyInputComponent : public OIS::KeyListener{
public:

	//Seguramente haya que pasarle un puntero al GameManager
	KeyInputComponent()
	{
		TutorialApplication::getInstance()->registerKeyInputObserver(this);	
	};

	virtual ~KeyInputComponent(){};

private:
};

#endif /* RENDERCOMPONENT_H_ */
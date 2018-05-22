#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "TutorialApplication.h"

//Componente que escucha los eventos de teclado
class KeyInputComponent : public OIS::KeyListener, public Component{
public:
	KeyInputComponent() : Component()
	{

		TutorialApplication::getInstance()->registerKeyInputObserver(this);
	};

	virtual ~KeyInputComponent(){};

};

#endif /* KEYINPUTCOMPONENT_H_*/
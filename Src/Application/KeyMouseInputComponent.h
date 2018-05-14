#ifndef KEYMOUSEINPUTCOMPONENT_H_
#define KEYMOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "TutorialApplication.h"

//Componente que escucha los eventos de teclado y de ratón
class KeyMouseInputComponent : public Component, public OIS::KeyListener, public OIS::MouseListener{
public:
	KeyMouseInputComponent() : Component()
	{
		TutorialApplication::getInstance()->registerKeyInputObserver(this);
		TutorialApplication::getInstance()->registerMouseInputObserver(this);

	};

	virtual ~KeyMouseInputComponent(){};

};

#endif /* KEYMOUSEINPUTCOMPONENT_H_*/
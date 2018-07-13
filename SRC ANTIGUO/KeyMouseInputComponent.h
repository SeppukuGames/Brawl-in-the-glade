#ifndef KEYMOUSEINPUTCOMPONENT_H_
#define KEYMOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "MainGame.h"

//Componente que escucha los eventos de teclado y de ratón
class KeyMouseInputComponent : public Component, public OIS::KeyListener, public OIS::MouseListener{
public:
	KeyMouseInputComponent() : Component()
	{
		MainGame::getInstance()->registerKeyInputObserver(this);
		MainGame::getInstance()->registerMouseInputObserver(this);

	};

	virtual ~KeyMouseInputComponent(){};

};

#endif /* KEYMOUSEINPUTCOMPONENT_H_*/
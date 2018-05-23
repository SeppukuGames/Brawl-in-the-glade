#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "MainGame.h"
#include "Home.h"

//Componente que escucha los eventos de teclado
class KeyInputComponent : public OIS::KeyListener,  public Component{
public:
	KeyInputComponent(int index) : Component()
	{
		if(index == 0)
			Home::getInstance()->registerKeyInputObserver(this);
		else 
			MainGame::getInstance()->registerKeyInputObserver(this);
	};

	virtual ~KeyInputComponent(){};

};

#endif /* KEYINPUTCOMPONENT_H_*/
#ifndef MOUSEINPUTCOMPONENT_H_
#define MOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "MainGame.h"

//Componente que escucha los eventos de ratón
class MouseInputComponent : public OIS::MouseListener{
public:

	MouseInputComponent()
	{
		MainGame::getInstance()->registerMouseInputObserver(this);
	};
	virtual ~MouseInputComponent(){};

};

#endif /* MOUSEINPUTCOMPONENT_H_ */
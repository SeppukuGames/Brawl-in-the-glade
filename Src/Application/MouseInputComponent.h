#ifndef MOUSEINPUTCOMPONENT_H_
#define MOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "TutorialApplication.h"

//Componente que escucha los eventos de ratón
class MouseInputComponent : public Component, public OIS::MouseListener{
public:

	MouseInputComponent()
	{
		TutorialApplication::getInstance()->registerMouseInputObserver(this);
	};
	virtual ~MouseInputComponent(){};

};

#endif /* MOUSEINPUTCOMPONENT_H_ */
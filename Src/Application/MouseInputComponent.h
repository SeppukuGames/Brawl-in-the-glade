#ifndef MOUSEINPUTCOMPONENT_H_
#define MOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "TutorialApplication.h"

class MouseInputComponent : public Component, public OIS::MouseListener{
public:
	//----------------------M�TODOS---------------------------

	MouseInputComponent() : Component()
	{
		TutorialApplication::getInstance()->registerMouseInputObserver(this);
	};
	virtual ~MouseInputComponent(){};
	//----------------------M�TODOS---------------------------


};

#endif /* RENDERCOMPONENT_H_ */
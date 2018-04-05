#ifndef MOUSEINPUTCOMPONENT_H_
#define MOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>

class MouseInputComponent : public Component, public OIS::MouseListener{
public:

	MouseInputComponent() : Component()
	{
		TutorialApplication::getInstance()->registerMouseInputObserver(this);
	};
	virtual ~MouseInputComponent(){};

private:
};

#endif /* RENDERCOMPONENT_H_ */
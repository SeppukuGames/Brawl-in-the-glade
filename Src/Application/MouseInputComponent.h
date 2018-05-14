#ifndef MOUSEINPUTCOMPONENT_H_
#define MOUSEINPUTCOMPONENT_H_

#include "Component.h"
#include "TutorialApplication.h"
#include <OIS.h>

class MouseInputComponent : public OIS::MouseListener, public Component{
public:

	MouseInputComponent()
	{
		TutorialApplication::getInstance()->registerMouseInputObserver(this);
	};
	virtual ~MouseInputComponent(){};

};

#endif /* RENDERCOMPONENT_H_ */
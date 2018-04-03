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

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

		int i = 0;

		switch (id)
		{
		case OIS::MB_Left:
			i++;
			break;

		default:
			break;
		}
		return true;
	};


	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
	{

		return true;
	};

	virtual bool mouseMoved(const OIS::MouseEvent &arg)
	{
		/*if (arg.state.buttonDown(OIS::MB_Right))
		{
		_gameObject->getNode()->yaw(Ogre::Degree(-rotation * arg.state.X.rel), Ogre::Node::TS_WORLD);
		_gameObject->getNode()->pitch(Ogre::Degree(-rotation * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
		}*/
		return true;
	}

private:
};

#endif /* RENDERCOMPONENT_H_ */

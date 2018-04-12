#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "KeyInputComponent.h"


class MoveComponent : public KeyInputComponent {
public:

	MoveComponent() : KeyInputComponent()
	{

	};
	virtual ~MoveComponent(){};

	virtual void start(){
		velocity = 50;
		direction = Ogre::Vector3::ZERO;
	};
	virtual void tick(double elapsed){
		_gameObject->getNode()->translate(direction * elapsed, Ogre::Node::TS_LOCAL);

	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.z = -velocity;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			direction.z = velocity;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			direction.x += -velocity;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			direction.x += velocity;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			direction.y = -velocity;
			break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
			direction.y = velocity;
			break;

		default:
			break;
		}
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){

		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.z = 0;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			direction.z = 0;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			direction.x -= -velocity;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			direction.x -= velocity;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			direction.y = 0;
			break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
			direction.y = 0;
			break;

		default:
			break;
		}
		return true;
	};

private:
	Ogre::Vector3 direction; 
	float velocity;

};

#endif /* MOVECOMPONENT_H_ */
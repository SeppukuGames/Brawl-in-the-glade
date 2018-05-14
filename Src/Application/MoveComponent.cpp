#include "MoveComponent.h"

MoveComponent::MoveComponent() : KeyInputComponent(){};

MoveComponent::~MoveComponent(){};

void MoveComponent::start(){
	velocity = 50;
	direction = Ogre::Vector3::ZERO;
	animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
};

void  MoveComponent::tick(double elapsed){
	_gameObject->getNode()->translate(direction* Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
	Ogre::Vector3 movement = direction*  (Ogre::Real) elapsed; //He añadido esto.
};

bool  MoveComponent::keyPressed(const OIS::KeyEvent &arg){
	switch (arg.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:

		direction.z += -velocity;

		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:

		direction.z += velocity;

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

		direction.y += -velocity;

		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:

		direction.y += velocity;
		break;

	case OIS::KC_SPACE:
		animComp->blend("Backflip", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);

		break;

	default:
		break;
	}

	animComp->blend("Walk", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
	return true;
};


bool  MoveComponent::keyReleased(const OIS::KeyEvent &arg){

	switch (arg.key)
	{
	case OIS::KC_UP:

	case OIS::KC_W:
		direction.z += velocity;

		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:

		direction.z += -velocity;

		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:

		direction.x += velocity;

		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:

		direction.x += -velocity;

		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:

		direction.y += velocity;

		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		direction.y += -velocity;
		break;

	case OIS::KC_SPACE:
		//animComp->setAnimation("Idle2", true);
		break;

	default:
		break;
	}
	animComp->blend("Idle2", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
	return true;
};
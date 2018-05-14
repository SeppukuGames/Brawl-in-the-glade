#include "MoveComponent.h"
#include <iostream>

MoveComponent::MoveComponent() : KeyInputComponent(){};

MoveComponent::~MoveComponent(){};

void MoveComponent::start(){
	velocity = 500;
	//direction = Ogre::Vector3::ZERO;
	animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
	direction = { 0, 0, 0 };
	oldDirection = direction;
};

void  MoveComponent::tick(double elapsed){

	if (oldDirection != direction) {
		rb->getRigidbody()->setLinearVelocity(direction * 10 * Ogre::Real(elapsed));
		oldDirection = direction;
	}
	//std::cout << "Direccion X: " << direction.getX() << "\n Direccion Z: " << direction.getZ() << std::endl;
	btTransform transform;
	rb->getRigidbody()->getMotionState()->getWorldTransform(transform);
	std::cout << "Transform X: " << transform.getOrigin().getX() << "\n Transform Z: " << transform.getOrigin().getZ() << std::endl;
	//_gameObject->getNode()->translate(direction* Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

	//PARA ROTAR EL PERSONAJE
	//rb->getRigidbody()->applyTorqueImpulse(btVector3(0, 100, 0));
};

bool  MoveComponent::keyPressed(const OIS::KeyEvent &arg){
	switch (arg.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		direction.setZ((-velocity));
		//direction.z += -velocity;

		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:

		direction.setZ((velocity));
		//direction.z += velocity;

		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:

		//direction.x += -velocity;
		direction.setX((-velocity));
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:

		//direction.x += velocity;
		direction.setX((velocity));
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:

		//direction.y += -velocity;

		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:

		//direction.y += velocity;
		break;

	case OIS::KC_SPACE:
		animComp->blend("Backflip", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
		break;

	default:
		break;
	}

	//E ORA DO MOVIMENTO
	animComp->blend("Walk", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
	return true;
};


bool  MoveComponent::keyReleased(const OIS::KeyEvent &arg){

	switch (arg.key)
	{
	case OIS::KC_UP:

	case OIS::KC_W:
		//direction.z += velocity;
		direction.setZ((0));
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:

		//direction.z += -velocity;
		direction.setZ((0));
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:

		//direction.x += velocity;
		direction.setX((0));
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:

		//direction.x += -velocity;
		direction.setX((0));

		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:

		//direction.y += velocity;

		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		//direction.y += -velocity;

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
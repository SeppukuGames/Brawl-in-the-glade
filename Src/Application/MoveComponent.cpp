#include "MoveComponent.h"
#include <iostream>


void MoveComponent::start() {
	velocity = 150;
	//direction = Ogre::Vector3::ZERO;
	animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
	player = dynamic_cast<PlayerComponent*> (_gameObject->getComponent(ComponentName::PLAYER));
	mouseComponent = dynamic_cast<MouseComponent*> (_gameObject->getComponent(ComponentName::MOUSE));
	direction = { 0, 0, 0 };
	transform = rb->getRigidbody()->getWorldTransform();
	lastRotation = transform.getRotation();
	
};

void MoveComponent::tick(double elapsed) {

	//rb->getRigidbody()->setLinearVelocity(direction *2);

	transform.setOrigin(transform.getOrigin() + direction * elapsed);
	//rb->getRigidbody()->setWorldTransform(transform);

	//transform.getRotation().getAngle();
	//transform.setRotation(mouseComponent->getRotation());	
	//
	rb->getRigidbody()->setCenterOfMassTransform(transform);
	rb->getRigidbody()->getMotionState()->setWorldTransform(transform);


	//NO BORRAR, ÚTIL PARA DEBUG
	//std::cout << "Direccion X: " << direction.getX() << "\n Direccion Z: " << direction.getZ() << std::endl;
	/*std::cout << "Velocity X: " << rb->getRigidbody()->getLinearVelocity().getX() <<
	"\n Velocity Y: " << rb->getRigidbody()->getLinearVelocity().getY() << "\n Velocity Z: " <<
	rb->getRigidbody()->getLinearVelocity().getZ() << std::endl;
	*/
	//std::cout << "Rotation X: " << transform.getRotation().getX() << "\n Rotation Y: " << transform.getRotation().getY() << "\n Rotation Z: " << transform.getRotation().getZ() << std::endl;
	//std::cout << "Transform X: " << transform.getOrigin().getX() << "\n Transform Y: " << transform.getOrigin().getY() << "\n Transform Z: " << transform.getOrigin().getZ() << std::endl;

	//DEBUG UI: BORRAR CUANDO TERMINEN LAS PRUEBAS
	if(player != NULL)
		player->updateUI();
};

bool MoveComponent::keyPressed(const OIS::KeyEvent &arg) {
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
		//animComp->blend("Backflip", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
		//resetCamPosition = true;
		break;

	default:
		break;
	}

	animComp->blend("Walk", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
	return true;
};

bool MoveComponent::keyReleased(const OIS::KeyEvent &arg) {

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
		//resetCamPosition = false;
		break;

	default:
		break;
	}

	animComp->blend("Idle2", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
	return true;
};
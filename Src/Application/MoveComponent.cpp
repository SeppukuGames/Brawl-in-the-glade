#include "MoveComponent.h"
#include <iostream>


void MoveComponent::start() {
	velocity = 150;
	//direction = Ogre::Vector3::ZERO;
	animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
	player = dynamic_cast<PlayerComponent*> (_gameObject->getComponent(ComponentName::PLAYER));
	direction = { 0, 0, 0 };
	//transform = rb->getRigidbody()->getWorldTransform();
	
};

void MoveComponent::tick(double elapsed) {

	Plane mPlane(Vector3::UNIT_Y, 0);

	std::pair<bool, Real> result = rayCast.intersects(mPlane);

	if (result.first) {
		// if the ray intersect the plane, we have a distance value
		// telling us how far from the ray origin the intersection occurred.
		// the last thing we need is the point of the intersection.
		// Ray provides us getPoint() function which returns a point
		// along the ray, supplying it with a distance value.
		//std::cout << "Entra!" << std::endl;
		// get the point where the intersection is
		Vector3 point = rayCast.getPoint(result.second);

		// assume that "forward" for the player in local-frame is +zAxis
		// and that the player is constrained to rotate about yAxis (+yAxis is "up")
		btVector3 localLook(0.0f, 0.0f, 1.0f); // zAxis
		btVector3 rotationAxis(0.0f, 1.0f, 0.0f); // yAxis

		btTransform transform = rb->getRigidbody()->getWorldTransform();
		btTransform identity = transform.getIdentity();
		btQuaternion rotation = transform.getRotation();
		btVector3 rotVector(rotation.getX(), rotation.getY(), rotation.getZ());
		// compute currentLook and angle
		btVector3 currentLook = localLook * rotVector * -rotation.getW();
		btVector3 newLook(point.x, 1, point.z);
		btScalar angle;

		if (point.x >= 0) {
			angle = currentLook.angle(newLook);
			angle = -angle;
		}
		else {
			angle = currentLook.angle(newLook);
		}
		
		
		// compute new rotation
		btQuaternion deltaRotation(rotationAxis, angle);
		btQuaternion newRotation = deltaRotation * rotation;

		std::cout << "Angulo rotacion: " << point.z << std::endl;
		// apply new rotation
		transform.setRotation(deltaRotation);
		transform.setOrigin(transform.getOrigin() + direction * elapsed);
		rb->getRigidbody()->setCenterOfMassTransform(transform);
		rb->getRigidbody()->getMotionState()->setWorldTransform(transform);

	}


	/*btTransform tr = rb->getRigidbody()->getCenterOfMassTransform();
	transform.setOrigin(transform.getOrigin() + direction * elapsed);
	//rb->getRigidbody()->setCenterOfMassTransform(transform);
	rb->getRigidbody()->getMotionState()->setWorldTransform(transform);
	*/

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

void MoveComponent::setMouseRay(Ray mouseRay) {
	rayCast = mouseRay;
}
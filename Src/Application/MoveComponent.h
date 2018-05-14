#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_



//using namespace Ogre;  Va a dar errores por esto.s

#include "Component.h"
#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
#include <iostream>

class MoveComponent : public KeyInputComponent, public Component {
public:

	MoveComponent() : KeyInputComponent(), Component()
	{
		
	};
	virtual ~MoveComponent(){};

	virtual void start(){
		velocity = 50;
		//direction = Ogre::Vector3::ZERO;
		animComp =  dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
		direction = { 0, 0, 0 };	
		transform.setIdentity();
	};

	virtual void tick(double elapsed){

		//rb->getRigidbody()->setLinearVelocity(direction *2);
		
		transform.setOrigin(transform.getOrigin() + direction * elapsed);
		rb->getRigidbody()->setWorldTransform(transform);
		rb->getRigidbody()->getMotionState()->setWorldTransform(transform);
		rb->getRigidbody()->setLinearVelocity(btVector3(0, 0, 0));

		//NO BORRAR, ÚTIL PARA DEBUG
		//std::cout << "Direccion X: " << direction.getX() << "\n Direccion Z: " << direction.getZ() << std::endl;
		/*std::cout << "Velocity X: " << rb->getRigidbody()->getLinearVelocity().getX() <<
			"\n Velocity Y: " << rb->getRigidbody()->getLinearVelocity().getY() << "\n Velocity Z: " <<
			rb->getRigidbody()->getLinearVelocity().getZ() << std::endl;
			*/		
		//std::cout << "Rotation X: " << transform.getRotation().getX() << "\n Rotation Y: " << transform.getRotation().getY() << "\n Rotation Z: " << transform.getRotation().getZ() << std::endl;
		//std::cout << "Transform X: " << transform.getOrigin().getX() << "\n Transform Y: " << transform.getOrigin().getY() << "\n Transform Z: " << transform.getOrigin().getZ() << std::endl;

	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
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

	virtual bool keyReleased(const OIS::KeyEvent &arg){

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


	btVector3 direction;

private:
	//Ogre::Vector3 direction; 
	float velocity;
	
	DynamicRigidbodyComponent* rb;
	//Puntero a la animacion
	AnimationComponent* animComp;

	btTransform transform;

	bool resetCamPosition;
};

#endif /* MOVECOMPONENT_H_ */
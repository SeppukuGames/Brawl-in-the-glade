#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_



//using namespace Ogre;  Va a dar errores por esto.s

#include "Component.h"
#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"


#include <iostream>
class MoveComponent : public KeyInputComponent {
public:

	MoveComponent() : KeyInputComponent()
	{

	};
	virtual ~MoveComponent(){};

	virtual void start(){
		velocity = 50;
		rotation = 0.13;
		direction = Ogre::Vector3::ZERO;
		sigueRotando = false;
		//Componente de animación
		animComp =  dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
	};

	virtual void tick(double elapsed){
		_gameObject->getNode()->translate(direction* elapsed, Ogre::Node::TS_LOCAL);
		Ogre::Vector3 movement = direction*  (Ogre::Real) elapsed; 
		if (sigueRotando){
			_gameObject->getNode()->yaw(Ogre::Degree(5 * rotation));
		}
	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
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

			//direction.y += -velocity;
			if (!sigueRotando) sigueRotando = true;
			

			//quatRot = Ogre::Quaternion(Ogre::Degree(5* rotation), Ogre::Vector3::UNIT_Y);
			//_gameObject->getNode()->setOrientation(quatRot);
			//
			//_gameObject->getNode()->rotate(quatRot, Ogre::Node::TS_LOCAL);
			//std::cout << _gameObject->getNode()->getOrientation() << std::endl; 
			break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
			//_gameObject->getNode()->yaw(Ogre::Degree(-5 * rotation));
			//direction.y += velocity; 
			//quatRot = Ogre::Quaternion(Ogre::Degree(-5 * rotation), Ogre::Vector3(1, 1, 0));
			
			//_gameObject->getNode()->rotate(quatRot);
			//_gameObject->getNode()->setOrientation(quatRot);
			break;

		case OIS::KC_SPACE:
		
			animComp->blend("Backflip", animComp->BlendWhileAnimating, 0.2, true);

			break;

		default:
			break;
		}

		//E ORA DO MOVIMENTO
		animComp->blend("Walk", animComp->BlendWhileAnimating, 0.2, true);
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){

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
			if (sigueRotando) sigueRotando = false;
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
		animComp->blend("Idle2", animComp->BlendWhileAnimating, 0.2, true);
		return true;
	};

private:
	//Rotaciones
	double rotation;
	Ogre::Quaternion quatRot;
	bool sigueRotando;
	//Direcciones
	Ogre::Vector3 direction; 
	float velocity;

	//Puntero a la animacion
	AnimationComponent* animComp;

};

#endif /* MOVECOMPONENT_H_ */
#ifndef ENEMYCOMPONENT_H_
#define ENEMYCOMPONENT_H_

//#include "GameComponent.h"
#include "Component.h"
#include <Ogre.h>
#include "GameObject.h"
#include "DynamicRigidbodyComponent.h"

class EnemyComponent : public Component {
public:

	EnemyComponent(){


	};

	virtual ~EnemyComponent(){};

	virtual void start(){
		rigidbodyComp = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));

		if (rigidbodyComp == NULL){
			throw std::invalid_argument("El componente no tiene rigidbody");
		}
		velocity = 0.15;
		direction = Ogre::Vector3::ZERO;
		
		
	};

	virtual void tick(double elapsed){
		obtenerDireccion();
		_gameObject->getNode()->translate(direction * elapsed, Ogre::Node::TS_LOCAL);
	};

	//Con la posicion del objetivo y la nuestra, calculamos la trayectoria y 
	//esta se irá sumando (con la velocidad) poco a poco hasta llegar al objetivo
	void obtenerDireccion(){
		direction = (Torre - _gameObject->getNode()->getPosition())*velocity;
	}

private:
	Ogre::Vector3 Torre = { 700, 0, 700 };
	Ogre::Vector3 direction;
	float velocity;
	DynamicRigidbodyComponent* rigidbodyComp;

};

#endif /* ENEMYCOMPONENT_H_ */
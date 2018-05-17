#ifndef ENEMIGO_H_
#define ENEMIGO_H_

//#include "GameComponent.h"
#include "Component.h"

class Enemigo : public Component {
public:

	Enemigo() : Component() 
	{

	};

	virtual ~Enemigo(){};

	virtual void start(){
		velocity = 0.15f;
		direction = Ogre::Vector3::ZERO;
	};

	virtual void tick(double elapsed){
		obtenerDireccion();
		_gameObject->getNode()->translate(direction * Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
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

};

#endif /* ENEMYCOMPONENT */
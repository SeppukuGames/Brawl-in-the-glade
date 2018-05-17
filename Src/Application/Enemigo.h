#ifndef ENEMIGO_H_
#define ENEMIGO_H_

//#include "GameComponent.h"
#include "Component.h"
#include "DynamicRigidbodyComponent.h"
#include <cmath> 
#include <iostream>

class Enemigo : public Component {
public:

	Enemigo() : Component() 
	{

	};

	virtual ~Enemigo(){};

	virtual void start(){
		
		velocity = 0.15f;
		life = maxLife;
		direction = { 0, 0, 0 };
		Torre = { 700, 0, 700 };
		objetivo = Torre;

		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
		
	};


	virtual void tick(double elapsed){	

		float dist = obtenerDistancia();
		if (dist < maxDistance) {
			//std::cout << "Reaching tower! Distance: " << dist << std::endl;
			objetivo = _player_rb->getRigidbody()->getWorldTransform().getOrigin();
		}
		else {
			objetivo = Torre;
		}
		obtenerDireccion();
		//_gameObject->getNode()->translate(direction * Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
		rb->getRigidbody()->getWorldTransform().setOrigin(rb->getRigidbody()->getWorldTransform().getOrigin() + direction * elapsed);
		rb->getRigidbody()->setWorldTransform(rb->getRigidbody()->getWorldTransform());
		rb->getRigidbody()->getMotionState()->setWorldTransform(rb->getRigidbody()->getWorldTransform());
		rb->getRigidbody()->setLinearVelocity(btVector3(0, 0, 0));
		
	};	


	float obtenerDistancia() {
		
		btVector3 pos1 = rb->getRigidbody()->getWorldTransform().getOrigin();			//Posición del enemigo
		btVector3 pos2 = _player_rb->getRigidbody()->getWorldTransform().getOrigin();	//Posición del jugador

		float distanceX = pow((float)pos2.getX() - (float)pos1.getX(), 2);
		float distanceZ = pow((float)pos2.getZ() - (float)pos1.getZ(), 2);

		return sqrt(distanceZ + distanceX);		//Cálculo de distancia
	}
	//Con la posicion del objetivo y la nuestra, calculamos la trayectoria y 
	//esta se irá sumando (con la velocidad) poco a poco hasta llegar al objetivo
	void obtenerDireccion(){
		//direction = (Torre - _gameObject->getNode()->getPosition())*velocity;
		direction = (objetivo - rb->getRigidbody()->getWorldTransform().getOrigin()) * velocity;
	}

	void setUpPlayer(GameObject* player) {
		_player = player;
		_player_rb = dynamic_cast<DynamicRigidbodyComponent*> (_player->getComponent(ComponentName::RIGIDBODY));

	}

private:
	//Ogre::Vector3 Torre = { 700, 0, 700 };
	//Ogre::Vector3 direction;
	btVector3 direction, Torre, objetivo;
	DynamicRigidbodyComponent* rb;
	DynamicRigidbodyComponent* _player_rb;
	float velocity;
	const float maxDistance = 150.f;	//Max distance between enemy-player
	GameObject* _player;				//Player Reference
	//Atributos del enemigo
	float life;							//La vida del enemigo en cada momento
	const float maxLife = 100;			//La vida máxima del enemigo como atributo
	const float attackPower = 50;		//El poder de ataque del enemigo

};

#endif /* ENEMYCOMPONENT */
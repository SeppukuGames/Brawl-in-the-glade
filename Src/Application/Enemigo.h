#ifndef ENEMIGO_H_
#define ENEMIGO_H_

//#include "GameComponent.h"
#include "Component.h"
#include "DynamicRigidbodyComponent.h"
#include "TowerComponent.h"
#include <cmath> 
#include <iostream>

enum objetiveType { _PLAYER, _TOWER, _NULL };

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
		timeCheck = 0;
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
		canMove = true;
		objType = _NULL;
	};


	virtual void tick(double elapsed){	

		pos1 = rb->getRigidbody()->getWorldTransform().getOrigin();			//Posición del enemigo
		pos2 = _player_rb->getRigidbody()->getWorldTransform().getOrigin();	//Posición del jugador
		dist = obtenerDistancia();
		
		if (dist < maxPlayerDistance) {
			
			//std::cout << "Reaching tower! Distance: " << dist << std::endl;
			objetivo = _player_rb->getRigidbody()->getWorldTransform().getOrigin();
			objType = _PLAYER;
			if (dist < fireDistance) {
				timeCheck += elapsed;
				//std::cout << " Time: " << timeCheck << std::endl;
				canMove = false;
				if (timeCheck >= fireCadence) {
					timeCheck = 0.f;
					Fire();
				}
			}
			else
				canMove = true;
				

			
		}
		else {
			pos2 = Torre;	//Posición de la torre
			dist = obtenerDistancia();
			objetivo = Torre;
			objType = _TOWER;
			

			if (dist < fireDistance) {	
				canMove = false;
				timeCheck += elapsed;
				if (timeCheck >= fireCadence) {
					timeCheck = 0.f;
					Fire();
				}
			}
			else
				canMove = true;
		}

		if (canMove) {
			obtenerDireccion();
			//_gameObject->getNode()->translate(direction * Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
			rb->getRigidbody()->getWorldTransform().setOrigin(rb->getRigidbody()->getWorldTransform().getOrigin() + direction * elapsed);
			rb->getRigidbody()->setWorldTransform(rb->getRigidbody()->getWorldTransform());
			rb->getRigidbody()->getMotionState()->setWorldTransform(rb->getRigidbody()->getWorldTransform());
			rb->getRigidbody()->setLinearVelocity(btVector3(0, 0, 0));
		}
	};	


	float obtenerDistancia() {
		
		//btVector3 pos1 = rb->getRigidbody()->getWorldTransform().getOrigin();			//Posición del enemigo
		//btVector3 pos2 = _player_rb->getRigidbody()->getWorldTransform().getOrigin();	//Posición del jugador

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

	void Fire() {

		//AQUÍ HAY QUE ANIMAR AL ENEMIGO PARA QUE ATAQUE

		if (objType == _PLAYER) {
			playerHealth = dynamic_cast <PlayerComponent*> (_player->getComponent(ComponentName::PLAYER));
			playerHealth->hitPlayer(attackPower);
		}
		else if (objType == _TOWER) {
			towerHealth->hitTower(attackPower);
		}
		else std::cout << "ERROR: Enemy objetive type not allowed!" << std::endl;
		
	}

	void setUpPlayer(GameObject* player) {
		_player = player;
		_player_rb = dynamic_cast<DynamicRigidbodyComponent*> (_player->getComponent(ComponentName::RIGIDBODY));

	}

	void setUpTower(GameObject* tower) {
		_tower = tower;
		towerHealth = dynamic_cast<TowerComponent*> (_tower->getComponent(ComponentName::TOWER));

	}

private:
	//Ogre::Vector3 Torre = { 700, 0, 700 };
	//Ogre::Vector3 direction;
	btVector3 direction, Torre, objetivo;
	DynamicRigidbodyComponent* rb;
	DynamicRigidbodyComponent* _player_rb;
	float velocity;
	const float maxPlayerDistance = 250.f;	//Max distance between enemy-player
	//const float maxTowerDistance = 250.f;	//Max distance between enemy-player
	const float fireDistance = 100.f;		//Distance of enemy's ability to fire
	GameObject* _player;					//Player Reference
	PlayerComponent* playerHealth;			//Player's health Reference
	GameObject* _tower;						//Tower Reference
	TowerComponent* towerHealth;			//Tower's health Reference
	const float fireCadence = 2.f;
	float timeCheck;
	bool canMove;

	btVector3 pos1, pos2;
	float dist;

	//Atributos del enemigo
	float life;							//La vida del enemigo en cada momento
	const float maxLife = 100;			//La vida máxima del enemigo como atributo
	const float attackPower = 50;		//El poder de ataque del enemigo
	objetiveType objType;

};

#endif /* ENEMYCOMPONENT */
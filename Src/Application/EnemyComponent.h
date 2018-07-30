#ifndef ENEMYCOMPONENT_H_
#define ENEMYCOMPONENT_H_

#include "Component.h"
#include "RigidbodyComponent.h"
/*
#include "DynamicRigidbodyComponent.h"
#include "TowerComponent.h"
#include "PlayerComponent.h"
#include <cmath> 
#include <iostream>
*/
enum objetiveType { _PLAYER, _TOWER, _NULL };
enum enemyType { ENEMY1, ENEMY2 };

class EnemyComponent : public Component {

public:



	EnemyComponent(enemyType type);

	virtual ~EnemyComponent();

	void Start();
	void Update(double elapsed);

	void EnemyComponent::EnemyAI(double elapsed);
	float EnemyComponent::obtenerDistancia(b2Vec2 pos1, b2Vec2 pos2);
	void EnemyComponent::obtenerDireccion();
	void EnemyComponent::Fire();
	void EnemyComponent::hitEmemy(float amount);


protected:

	b2Vec2 direction, Torre, objetivo;

	float velocity;
	float timeCheck;
	bool canMove;
	bool isDead;

	//UI
	//BillboardSet* enemyUI;
	//float maxWidth, maxHeight;

	//Atributos del enemigo
	objetiveType objType;					//Tipo de entidad a la que está atacando (player/torre)
	enemyType	enmType;					//Tipo de enemigo a construir

	const float maxPlayerDistance = 250.f;	//Max distance between enemy-player
	const float fireDistance = 100.f;		//Distance of enemy's ability to fire
	const float fireCadence = 2.f;			//Amount of seconds between each attack

	RigidbodyComponent* rb;					//Enemy's Rigidbody
	//GameObject* _player;					//Player Reference
	//PlayerComponent* playerHealth;			//Player's health Reference
	//GameObject* _tower;						//Tower Reference
	//TowerComponent* towerHealth;			//Tower's health Reference


};
#endif
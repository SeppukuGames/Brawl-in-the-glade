#include "EnemyComponent.h"
#include "StatsComponent.h"
#include "CanvasComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Error.h"
#include "EntityComponent.h"
#include "GameManager.h"
#include <iostream>


EnemyComponent::EnemyComponent(enemyType type) : Component(){
	enmType = type;
};

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Start(){

	//TODO ESTO DEBE IR POR XML
	switch (enmType) {
	case ENEMY1:
		velocity = 10.15f;
		gameObject->AddComponent(new EntityComponent("bot1.mesh"));
		break;
	case ENEMY2:
		velocity = 2.08f;
		gameObject->AddComponent(new EntityComponent("bot2.mesh"));
		break;
	default:
		Error errorE("\n\n\n\n\nERROR (ENEMY): El tipo de enemigo no esta definido ");
		throw errorE;
		break;
	}

	GameObject* tower_go = SceneManager::GetInstance()->GetCurrentScene()->GetTower();
	Torre.Set(tower_go->GetNode()->getPosition().x, tower_go->GetNode()->getPosition().z);
	direction = { 0, 0 };
	objetivo = Torre;
	timeCheck = 0;
	rb = (RigidbodyComponent*)gameObject->GetComponent(ComponentName::RIGIDBODY);
	canMove = true;
	isDead = false;
	objType = _NULL;
}

void EnemyComponent::Update(double elapsed){

	//No encuentra el componente de stats
	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	
	//If estas muerto
	if (stats->isDead()){
		isDead = true;
		GameManager::GetInstance()->RemoveEnemy();
		SceneManager::GetInstance()->GetCurrentScene()->Destroy(gameObject);
		return;
	}

	EnemyAI(elapsed);
}

void EnemyComponent::EnemyAI(double elapsed){
	
	//Prerrequisites
	b2Vec2 pos1 = rb->GetBody()->GetPosition();		//Posición del enemigo
	RigidbodyComponent* player_rb = (RigidbodyComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->
		GetComponent(ComponentName::RIGIDBODY);
	b2Vec2 pos2 = player_rb->GetBody()->GetPosition();	//Posición del jugador
	float dist = obtenerDistancia(pos1, pos2);

	//std::cout << "Distance: " << dist << std::endl;

	if (dist < maxPlayerDistance && !isDead) {
		std::cout << "Reaching player! Distance: " << dist << std::endl;
		objetivo = player_rb->GetBody()->GetPosition();
		objType = _PLAYER;
		
		if (dist < fireDistance) {
			timeCheck += elapsed;
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
		dist = obtenerDistancia(pos1, pos2);
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
		//std::cout << "DireccionX: " << objetivo.x << "\nDireccionY: " << objetivo.y << std::endl;
		b2Vec2 newVec(direction.x, direction.y);
		newVec *= elapsed;
		rb->GetBody()->SetLinearVelocity(newVec);
	}
	else{
		rb->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	}
}
float EnemyComponent::obtenerDistancia(b2Vec2 pos1, b2Vec2 pos2) {

	float distanceX = pow((float)pos2.x - (float)pos1.x, 2);
	float distanceZ = pow((float)pos2.y - (float)pos1.y, 2);

	return sqrt(distanceZ + distanceX);		//Cálculo de distancia
}

/*
Con la posicion del objetivo y la nuestra, calculamos la trayectoria y
esta se irá sumando (con la velocidad) poco a poco hasta llegar al objetivo
*/
void EnemyComponent::obtenerDireccion(){
	direction = (objetivo - rb->GetBody()->GetPosition());
	direction *= velocity;
}

void EnemyComponent::Fire() {

	//AQUÍ HAY QUE ANIMAR AL ENEMIGO PARA QUE ATAQUE
	
	/*StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	CanvasComponent* canvas = (CanvasComponent*)gameObject->GetComponent(ComponentName::CANVAS);
	*/
	if (objType == _PLAYER) {
		GameObject* player = SceneManager::GetInstance()->GetCurrentScene()->GetPlayer();
		StatsComponent* p_stats = (StatsComponent*)player->GetComponent(ComponentName::STATS);
		StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);

		p_stats->HitGameObject(stats->GetAttackPower());
	}
	else if (objType == _TOWER) {
		GameObject* tower = SceneManager::GetInstance()->GetCurrentScene()->GetTower();
		StatsComponent* t_stats = (StatsComponent*)tower->GetComponent(ComponentName::STATS);
		StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);

		t_stats->HitGameObject(stats->GetAttackPower());
		
	}
	else{
		Error errorE("\n\n\n\n\nERROR (ENEMY_COMP): El objetivo de ataque del enemigo no está definido! ");
		throw errorE;
	} 
	
}

enemyType EnemyComponent::GetEnemyType(){
	return enmType;
}

#include "EnemyComponent.h"
#include "StatsComponent.h"
#include "CanvasComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
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
		velocity = 0.15f;
		//life = maxLife = 100.f;
		//attackPower = 50.f;
		break;
	case ENEMY2:
		velocity = 0.08f;
		//life = maxLife = 200.f;
		//attackPower = 80.f;
		break;
	default:
		break;
	}

	direction = { 0, 0 };
	Torre = { 700, 700 };
	objetivo = Torre;
	timeCheck = 0;
	rb = (RigidbodyComponent*)gameObject->GetComponent(ComponentName::RIGIDBODY);
	canMove = true;
	isDead = false;
	objType = _NULL;
}

void EnemyComponent::Update(double elapsed){

	EnemyAI(elapsed);
}

void EnemyComponent::EnemyAI(double elapsed){
	
	//Prerrequisites
	b2Vec2 pos1 = rb->GetBody()->GetPosition();		//Posición del enemigo
	RigidbodyComponent* player_rb = (RigidbodyComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->
		GetComponent(ComponentName::RIGIDBODY);
	b2Vec2 pos2 = player_rb->GetBody()->GetPosition();	//Posición del jugador
	float dist = obtenerDistancia(pos1, pos2);

	//If estas muerto
	/*if (life <= 0){
	isDead = true;
	MainGame::getInstance()->DestroyGameObject(_gameObject);
	}*/

	if (dist < maxPlayerDistance && !isDead) {
		//std::cout << "Reaching tower! Distance: " << dist << std::endl;
		objetivo = player_rb->GetBody()->GetPosition();
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
		b2Vec2 newVec(rb->GetBody()->GetPosition().x + direction.x,
			rb->GetBody()->GetPosition().y + direction.y);
		newVec *= elapsed;
		rb->GetBody()->SetTransform(newVec, rb->GetBody()->GetAngle());
		//rb->GetBody()->SetTransform(rb->getRigidbody()->getWorldTransform());
		//rb->GetBody()->getMotionState()->setWorldTransform(rb->getRigidbody()->getWorldTransform());
		rb->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	}
}
float EnemyComponent::obtenerDistancia(b2Vec2 pos1, b2Vec2 pos2) {

	//btVector3 pos1 = rb->getRigidbody()->getWorldTransform().getOrigin();			//Posición del enemigo
	//btVector3 pos2 = _player_rb->getRigidbody()->getWorldTransform().getOrigin();	//Posición del jugador

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
		StatsComponent* stats = (StatsComponent*)player->GetComponent(ComponentName::STATS);

		stats->HitGameObject(stats->GetAttackPower());
	}
	else if (objType == _TOWER) {
		//towerHealth->hitTower(attackPower);
		GameObject* tower = SceneManager::GetInstance()->GetCurrentScene()->GetTower();
		StatsComponent* stats = (StatsComponent*)tower->GetComponent(ComponentName::STATS);

		stats->HitGameObject(stats->GetAttackPower());
		
	}
	else std::cout << "ERROR: Enemy objetive type not allowed!" << std::endl;
	

	
}

//ESTO HACERLO EN EL COMPONENTE DEL CANVAS DIRECTAMENTE LLAMÁNDOLO (IGUAL ARRIBA)
/*void EnemyComponent::hitEmemy(float amount) {
	life -= amount;
	enemyUI->setDefaultDimensions((maxWidth * life) / maxLife, maxHeight);
}*/
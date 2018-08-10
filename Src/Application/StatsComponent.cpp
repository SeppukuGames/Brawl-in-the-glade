#include "StatsComponent.h"

#include "GameObject.h"
#include "CanvasComponent.h"
#include "EnemyComponent.h"
#include "Error.h"

void StatsComponent::Start() {
	
	if (gameObject->GetTag() == "Tower"){
		life = maxLife = 1000;
		attackPower = 0;

		gameObject->GetNode()->setPosition(500, 0, 500);
		gameObject->GetNode()->setScale(10, 10, 10);
	}
	else if (gameObject->GetTag() == "Player"){
		life = maxLife = 150;
		attackPower = 15;

		gameObject->GetNode()->setPosition(0, 0, 0);
		gameObject->GetNode()->setScale(.5, .5, .5);
	}
	else if (gameObject->GetTag() == "Enemy"){
		EnemyComponent* enemyType = (EnemyComponent*)gameObject->GetComponent(ComponentName::ENEMY);
		RigidbodyComponent* rb = (RigidbodyComponent*)gameObject->GetComponent(ComponentName::RIGIDBODY);
		
		switch (enemyType->GetEnemyType()){
		
		case(enemyType::ENEMY1) :
			life = maxLife = 50;
			attackPower = 5;
			gameObject->GetNode()->setScale(1.5, 1.5, 1.5);
			SetEnemyWave(rb);
			break;

		case(enemyType::ENEMY2) :
			life = maxLife = 75;
			attackPower = 15;
			gameObject->GetNode()->setScale(1.5, 1.5, 1.5);
			SetEnemyWave(rb);
			break;

		default:
			break;
		}
	}
	else {

		Error errorE("\n\n\n\n\nERROR (STATS): El tag de la entidad no esta definido ");
		throw errorE;
	}
}

void StatsComponent::HitGameObject(float amount)
{
	life -= amount;
	CanvasComponent* canvas = (CanvasComponent*)gameObject->GetComponent(ComponentName::CANVAS);
	canvas->HitGameObject(amount);
};

void StatsComponent::SetEnemyWave(RigidbodyComponent* rb){

	b2Vec2 spawn1(-200, -200);
	b2Vec2 spawn2(850, -200);
	b2Vec2 spawn3(500, 850);

	srand((unsigned int)time(NULL));
	int random = rand() % 3;
	switch (random)
	{
	case 1:
		rb->GetBody()->SetTransform(spawn1, rb->GetBody()->GetAngle());
		break;
	case 2:
		rb->GetBody()->SetTransform(spawn2, rb->GetBody()->GetAngle());
		break;
	case 3:
		rb->GetBody()->SetTransform(spawn3, rb->GetBody()->GetAngle());
		break;
	default:
		break;
	}
	
	rb->GetBody()->SetTransform(b2Vec2(250, 250), rb->GetBody()->GetAngle());
}

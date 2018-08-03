#include "BulletComponent.h"

#include "SceneManager.h"
#include "StatsComponent.h"
#include "PlayerComponent.h"
#include <iostream>

BulletComponent::BulletComponent() : Component()
{
}


BulletComponent::~BulletComponent()
{
}

void BulletComponent::Start(){
	cont = .0;

	rb = (RigidbodyComponent*)gameObject->GetComponent(ComponentName::RIGIDBODY);
	rb->GetBody()->SetBullet(true);

	RigidbodyComponent* player_rb = (RigidbodyComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->GetComponent(ComponentName::RIGIDBODY);
	rb->GetBody()->SetTransform(player_rb->GetBody()->GetPosition(), player_rb->GetBody()->GetAngle());
	direccion.x = cos(rb->GetBody()->GetAngle());
	direccion.y = sin(rb->GetBody()->GetAngle());
}

void BulletComponent::Update(double elapsed){
	cont += elapsed;

	if (cont > bulletDuration)
		DestruyeBala();
	else{		
		
		direccion.x *= elapsed;
		direccion.y *= elapsed;
		rb->GetBody()->SetLinearVelocity(direccion);
	}
}

void BulletComponent::OnCollisionEnter(ColliderComponent* collider){

	std::cout << "Colision con " + collider->GetGameObject()->GetNode()->getName() + '\n';
	
	//Detectamos de que tipo es la colisión de esta manera
	if (collider->GetGameObject()->GetTag() == "Enemy"){
		StatsComponent* stats = (StatsComponent*)collider->GetGameObject()->GetComponent(ComponentName::STATS);
		stats->HitGameObject(10.f);	//CAMBIAR
		//DestruyeBala();
	}

}

void BulletComponent::DestruyeBala(){
	SceneManager::GetInstance()->GetCurrentScene()->RemoveGameObject(gameObject);
}


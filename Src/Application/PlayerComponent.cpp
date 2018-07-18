#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Error.h"
#include <Box2D.h>
#include <iostream>
#include "GameManager.h"

PlayerComponent::PlayerComponent() : rigidbody(nullptr)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start(){

	rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));
	velocity.Set(0, 0);
	angle = 0.0f;

	if (rigidbody == nullptr){
		Error errorE("\n\n\n\n\nError al crear el PlayerComponent. Necesita un Rigidbody ");
		throw errorE;
	}

	//rigidbody->GetBody()->SetAngularVelocity(-10.0f);
}

void PlayerComponent::Update(double elapsed){
	
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_A))
		velocity.y += 10;

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_Z))
		velocity.y += -10;

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_Q))
		angle = -100.0f;

	rigidbody->GetBody()->SetLinearVelocity(velocity);
	rigidbody->GetBody()->SetAngularVelocity(angle);

	//Acceso a la instancia de GameManager
	GameManager::GetInstance()->GetGameObject()->GetNode()->getName();

	//rigidbody->GetBody()->ApplyForce(velocity,rigidbody->GetBody()->GetWorldCenter(),true);
}

void PlayerComponent::OnCollisionEnter(ColliderComponent* collider){
	std::cout << "Entra en con Colisi�n con" + collider->GetGameObject()->GetNode()->getName() + '\n';
}

void PlayerComponent::OnCollisionExit(ColliderComponent* collider){
	std::cout << "Sale de la Colisi�n con" + collider->GetGameObject()->GetNode()->getName() + '\n';
}
#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Error.h"
#include <Box2D.h>
#include <iostream>

PlayerComponent::PlayerComponent() : rigidbody(nullptr)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start(){

	rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));

	if (rigidbody == nullptr){
		Error errorE("\n\n\n\n\nError al crear el PlayerComponent. Necesita un Rigidbody ");
		throw errorE;
	}

	//rigidbody->GetBody()->SetAngularVelocity(-10.0f);
}

void PlayerComponent::Update(double elapsed){
	b2Vec2 velocity(0, 0);
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_A))
		velocity.x += 10;

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_Z))
		velocity.x += -10;

	if (velocity.x != 0 || velocity.y != 0)
		rigidbody->GetBody()->SetLinearVelocity(velocity);

	//rigidbody->GetBody()->ApplyForce(velocity,rigidbody->GetBody()->GetWorldCenter(),true);
}

void PlayerComponent::OnCollisionEnter(ColliderComponent* collider){
	std::cout << "Entra en con Colisi�n con" + collider->GetGameObject()->GetName() + '\n';
}

void PlayerComponent::OnCollisionExit(ColliderComponent* collider){
	std::cout << "Sale de la Colisi�n con" + collider->GetGameObject()->GetName() + '\n';
}
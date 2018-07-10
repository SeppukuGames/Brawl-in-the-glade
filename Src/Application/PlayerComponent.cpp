#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Error.h"
#include <Box2D.h>

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

}
void PlayerComponent::Update(double elapsed){
	b2Vec2 velocity(0, 0);
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_A))
		velocity.y += 10;

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_Z))
		velocity.y += -10;

	rigidbody->GetBody()->SetLinearVelocity(velocity);
	//rigidbody->GetBody()->ApplyForce(velocity,rigidbody->GetBody()->GetWorldCenter(),true);
}
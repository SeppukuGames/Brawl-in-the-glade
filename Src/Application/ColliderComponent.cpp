#include "ColliderComponent.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include <Ogre.h>

ColliderComponent::ColliderComponent() : body(nullptr), pos(0, 0), angle(0)
{
}

ColliderComponent::~ColliderComponent(){
}

void ColliderComponent::Start(){
	pos.Set(gameObject->GetNode()->getPosition().x, gameObject->GetNode()->getPosition().y);
	Ogre::Vector3 rotation = gameObject->GetNode()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	angle = rotation.z -OFFSET;

	CreateBody();
}

void ColliderComponent::CreateBody(){
	//1. Definir body
	b2BodyDef *bd = new b2BodyDef();
	bd->type = b2BodyType::b2_staticBody;
	bd->position.Set(pos.x, pos.y);
	bd->angle = angle;

	//2. Crear body
	body = PhysicsManager::GetInstance()->GetWorld()->CreateBody(bd);

	//Guardamos el GameObject para poder detectar con quién colisiona
	body->SetUserData(gameObject);
}
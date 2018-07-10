#include "ColliderComponent.h"
#include "PhysicsManager.h"

ColliderComponent::ColliderComponent(b2Vec2 pos) :
pos(pos), body(nullptr)
{
}

ColliderComponent::~ColliderComponent(){
}

void ColliderComponent::CreateBody(){
	//1. Definir body
	b2BodyDef *bd = new b2BodyDef();
	bd->type = b2BodyType::b2_staticBody;
	bd->position.Set(pos.x, pos.y);

	//2. Crear body
	body = PhysicsManager::GetInstance()->GetWorld()->CreateBody(bd);
}
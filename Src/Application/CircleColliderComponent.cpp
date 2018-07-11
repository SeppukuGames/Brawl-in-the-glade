#include "CircleColliderComponent.h"
#include "PhysicsManager.h"

CircleColliderComponent::CircleColliderComponent(float radius) :
ColliderComponent(), radius(radius)
{
}

CircleColliderComponent::~CircleColliderComponent(){
}

void CircleColliderComponent::Start(){

	ColliderComponent::Start();

	CreateCollider();
}

void CircleColliderComponent::CreateCollider()
{
	//3. Crear Shape
	b2CircleShape * cs = new b2CircleShape();
	cs->m_radius = radius/2;

	//4. Crear Fixture
	b2FixtureDef *fd = new b2FixtureDef();
	fd->shape = cs;

	fd->density = DEFAULTDENSITY;
	fd->friction = DEFAULTFRICTION;
	fd->restitution = DEFAULTRESTITUTION;

	//5. Adjuntar Shape al cuerpo con Fixture
	body->CreateFixture(fd);
}


#include "BoxColliderComponent.h"
#include "PhysicsManager.h"

BoxColliderComponent::BoxColliderComponent(b2Vec2 pos, float w, float h) :
ColliderComponent(pos), w(w), h(h)
{
}

BoxColliderComponent::~BoxColliderComponent(){
}

void BoxColliderComponent::Start(){

	CreateBody();

	CreateCollider();
}

void BoxColliderComponent::CreateCollider()
{
	//3. Crear Shape
	b2PolygonShape *ps = new b2PolygonShape();
	ps->SetAsBox(w / 2, h / 2);

	//4. Crear Fixture
	b2FixtureDef *fd = new b2FixtureDef();
	fd->shape = ps;

	fd->density = DEFAULTDENSITY;
	fd->friction = DEFAULTFRICTION;
	fd->restitution = DEFAULTRESTITUTION;

	//5. Adjuntar Shape al cuerpo con Fixture
	body->CreateFixture(fd);
}


#include "BoxColliderComponent.h"
#include "PhysicsManager.h"

BoxColliderComponent::BoxColliderComponent(float w, float h, PhysicsMaterial material) :
ColliderComponent(material), w(w), h(h)
{
}

BoxColliderComponent::~BoxColliderComponent(){
}

b2Shape* BoxColliderComponent::CreateShape()
{
	//3. Crear Shape
	b2PolygonShape *ps = new b2PolygonShape();
	ps->SetAsBox(w / 2, h / 2);

	return ps;
}


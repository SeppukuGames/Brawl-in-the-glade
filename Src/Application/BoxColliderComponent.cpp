#include "BoxColliderComponent.h"
#include "PhysicsManager.h"

BoxColliderComponent::BoxColliderComponent(float w, float h, PhysicsMaterial material) :
ColliderComponent(material), w(w), h(h)
{
}

BoxColliderComponent::~BoxColliderComponent(){
}

//3. Método que construye la forma del objeto (Cubo en este caso)
b2Shape* BoxColliderComponent::CreateShape()
{
	b2PolygonShape *ps = new b2PolygonShape();
	ps->SetAsBox(w / 2, h / 2); 

	return ps;
}


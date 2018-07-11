#include "CircleColliderComponent.h"
#include "PhysicsManager.h"

CircleColliderComponent::CircleColliderComponent(float radius, PhysicsMaterial material) :
ColliderComponent(material), radius(radius)
{
}

CircleColliderComponent::~CircleColliderComponent(){
}

b2Shape* CircleColliderComponent::CreateShape()
{
	//3. Crear Shape
	b2CircleShape * cs = new b2CircleShape();
	cs->m_radius = radius/2;

	return cs;
}


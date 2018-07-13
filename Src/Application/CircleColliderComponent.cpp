#include "CircleColliderComponent.h"
#include "PhysicsManager.h"

CircleColliderComponent::CircleColliderComponent(float radius, PhysicsMaterial material) :
ColliderComponent(material), radius(radius)
{
}

CircleColliderComponent::~CircleColliderComponent(){
}

//3. M�todo que construye la forma del objeto (C�rculo en este caso)
b2Shape* CircleColliderComponent::CreateShape()
{
	b2CircleShape * cs = new b2CircleShape();
	cs->m_radius = radius/2;

	return cs;
}


#ifndef __CircleColliderComponent_h_
#define __CircleColliderComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class CircleColliderComponent : public ColliderComponent{

#pragma region Attributes  
private:
	float radius;

#pragma endregion Attributes

#pragma region Methods  

public:
	CircleColliderComponent(float radius, PhysicsMaterial material = PhysicsMaterial());
	virtual ~CircleColliderComponent();

private:
	virtual b2Shape* CreateShape();

#pragma endregion Methods

};

#endif /* __CircleColliderComponent_h_ */
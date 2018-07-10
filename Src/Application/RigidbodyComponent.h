#ifndef __RigidbodyComponent_h_
#define __RigidbodyComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class RigidbodyComponent : public Component{

#pragma region Attributes  
private:
	float density, friction,restitution;
	bool kinematic;
	b2Body *body;	//Referencia al body de CollisionComponent

#pragma endregion Attributes

#pragma region Methods  

public:
	RigidbodyComponent(bool kinematic = false, float density = DEFAULTDENSITY, float friction = DEFAULTFRICTION, float restitution = DEFAULTRESTITUTION);
	virtual ~RigidbodyComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	inline b2Body * GetBody(){ return body; };

private:
#pragma endregion Methods

};

#endif /* __RigidbodyComponent_h_ */
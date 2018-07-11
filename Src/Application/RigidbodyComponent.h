#ifndef __RigidbodyComponent_h_
#define __RigidbodyComponent_h_

#include "Box2D.h"
#include "ColliderComponent.h"

class RigidbodyComponent : public Component{

#pragma region Attributes  
private:
	float density;
	bool kinematic;
	b2Body *body;	//Referencia al body de CollisionComponent

#pragma endregion Attributes

#pragma region Methods  

public:
	RigidbodyComponent(bool kinematic = false, float density = DEFAULTDENSITY);
	virtual ~RigidbodyComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	inline b2Body * GetBody(){ return body; };

private:
#pragma endregion Methods

};

#endif /* __RigidbodyComponent_h_ */
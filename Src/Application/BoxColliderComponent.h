#ifndef __BoxColliderComponent_h_
#define __BoxColliderComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class BoxColliderComponent : public ColliderComponent{

#pragma region Attributes  
private:
	float w, h;

#pragma endregion Attributes

#pragma region Methods  

public:
	BoxColliderComponent(b2Vec2 pos, float w, float h);
	virtual ~BoxColliderComponent();

	virtual void Start();

private:
	virtual void CreateCollider();

#pragma endregion Methods
	
};

#endif /* __BoxColliderComponent_h_ */
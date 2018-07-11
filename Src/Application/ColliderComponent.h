#ifndef __ColliderComponent_h_
#define __ColliderComponent_h_

#include "Component.h"
#include "Box2D.h"

#define DEFAULTDENSITY 1000000
#define DEFAULTFRICTION 1.0f
#define DEFAULTRESTITUTION 1.0f
#define OFFSET 90.0f

class ColliderComponent : public Component{

#pragma region Attributes  

protected:
	b2Vec2 pos;
	float angle;

	b2Body* body;

#pragma endregion Attributes

#pragma region Methods

public:
	ColliderComponent();
	virtual ~ColliderComponent();

	virtual void Start();

	inline b2Body* GetBody(){ return body; }

protected:
	virtual void CreateBody();
	virtual void CreateCollider() = 0;

#pragma endregion Methods

};

#endif /* __BoxColliderComponent_h_ */
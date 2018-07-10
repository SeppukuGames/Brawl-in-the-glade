#ifndef __ColliderComponent_h_
#define __ColliderComponent_h_

#include "Component.h"
#include "Box2D.h"

#define DEFAULTDENSITY 1
#define DEFAULTFRICTION 0.3f
#define DEFAULTRESTITUTION 0.5f

class ColliderComponent : public Component{

#pragma region Attributes  

protected:
	b2Vec2 pos;
	b2Body* body;

#pragma endregion Attributes

#pragma region Methods

public:
	ColliderComponent(b2Vec2 pos);
	virtual ~ColliderComponent();

	inline b2Body* GetBody(){ return body; }

protected:
	virtual void CreateBody();
	virtual void CreateCollider() = 0;

#pragma endregion Methods

};

#endif /* __BoxColliderComponent_h_ */
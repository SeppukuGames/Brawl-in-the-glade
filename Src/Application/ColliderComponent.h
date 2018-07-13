#ifndef __ColliderComponent_h_
#define __ColliderComponent_h_

#include "Component.h"
#include "Box2D.h"

#define DEFAULTDENSITY 1
#define DEFAULTFRICTION 0.5f
#define DEFAULTRESTITUTION 0.3f
#define OFFSET 90.0f

struct PhysicsMaterial{
	float friction = DEFAULTFRICTION;
	float restitution = DEFAULTRESTITUTION;
};

class ColliderComponent : public Component{

#pragma region Attributes  

protected:
	b2Vec2 pos;					//Posici�n del collider
	float angle;				//�ngulo del collider
	PhysicsMaterial material;	//Material del collider

	b2Body* body;

#pragma endregion Attributes

#pragma region Methods

public:
	ColliderComponent(PhysicsMaterial material = PhysicsMaterial());
	virtual ~ColliderComponent();

	virtual void Start();

	inline b2Body* GetBody(){ return body; }

protected:
	virtual void CreateBody();								//M�todo encargado de crear un body del objeto
	virtual b2Shape* CreateShape() = 0;						//M�todo abstracto para crear el shape del objeto
	virtual void CreateFixture(b2Shape* shape);				//M�todo encargado de crear el fixture del objeto para asociarla al body


#pragma endregion Methods

};

#endif /* __BoxColliderComponent_h_ */
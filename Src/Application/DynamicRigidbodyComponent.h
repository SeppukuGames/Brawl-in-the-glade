#ifndef _DYNAMICRIGIDBODYCOMPONENT_H_
#define _DYNAMICRIGIDBODYCOMPONENT_H_

#include "RigidbodyComponent.h"

//Rigidbody dinámico. Es asociado a objetos físicos que tienen movimiento 
class DynamicRigidbodyComponent : public RigidbodyComponent
{
public:
	DynamicRigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia);
	~DynamicRigidbodyComponent();

	virtual void start();
	virtual void tick(double elapsed);


	inline btRigidBody * getRigidbody(){ return rigidBody; }
};

#endif /* _DYNAMICRIGIDBODYCOMPONENT_H_*/
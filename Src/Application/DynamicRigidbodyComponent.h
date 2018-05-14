#ifndef _DYNAMICRIGIDBODYCOMPONENT_H_
#define _DYNAMICRIGIDBODYCOMPONENT_H_

#include "RigidbodyComponent.h"

//Rigidbody din�mico. Es asociado a objetos f�sicos que tienen movimiento 
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
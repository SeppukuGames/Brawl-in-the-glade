#ifndef _DYNAMICRIGIDBODYCOMPONENT_H_
#define _DYNAMICRIGIDBODYCOMPONENT_H_

#include "RigidbodyComponent.h"

class DynamicRigidbodyComponent : public RigidbodyComponent
{
public:
	DynamicRigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia);
	~DynamicRigidbodyComponent();

	virtual void start();

	inline btRigidBody * getRigidbody(){ return rigidBody; }
};

#endif /* _DYNAMICRIGIDBODYCOMPONENT_H_*/
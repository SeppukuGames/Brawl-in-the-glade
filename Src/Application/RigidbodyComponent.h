#ifndef _RIGIDBODYCOMPONENT_H_
#define _RIGIDBODYCOMPONENT_H_

#include "Component.h"
#include "btBulletCollisionCommon.h"

class RigidbodyComponent : public Component{
public:
	RigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia);
	virtual ~RigidbodyComponent();

	virtual void start();
	virtual void tick(double elapsed);

protected:
	btRigidBody* rigidBody;

};

#endif /* _RIGIDBODYCOMPONENT_H_*/
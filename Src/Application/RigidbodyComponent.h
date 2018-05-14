#ifndef _RIGIDBODYCOMPONENT_H_
#define _RIGIDBODYCOMPONENT_H_

#include "Component.h"
#include "btBulletCollisionCommon.h"

//Rigidbody estático. Es asociado a gameObject que no tienen movimiento y son colisionables
class RigidbodyComponent : public Component{
public:
	RigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia);
	virtual ~RigidbodyComponent();

	virtual void start();

protected:
	btRigidBody* rigidBody;

};

#endif /* _RIGIDBODYCOMPONENT_H_*/
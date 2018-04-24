#ifndef _DYNAMICRIGIDBODYCOMPONENT_H_
#define _DYNAMICRIGIDBODYCOMPONENT_H_

#include "RigidbodyComponent.h"

class DynamicRigidbodyComponent : public RigidbodyComponent
{
public:
	DynamicRigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia);
	~DynamicRigidbodyComponent();

	virtual void start();
	virtual void tick(double elapsed);

	inline btRigidBody * getRigidbody(){ return rigidBody; }


	inline void setPos(btVector3 pos){
		
		//set the initial position and transform. For this demo, we set the tranform to be none
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(pos);


		//actually contruvc the body and add it to the dynamics world
		//Esfera a 50 metros de altura
		btDefaultMotionState *fallMotionState = new btDefaultMotionState(startTransform); 
		rigidBody->setMotionState(fallMotionState);
	}
};

#endif /* _DYNAMICRIGIDBODYCOMPONENT_H_*/
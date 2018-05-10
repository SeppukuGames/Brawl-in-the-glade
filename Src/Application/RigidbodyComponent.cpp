#include "RigidbodyComponent.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "TutorialApplication.h"

RigidbodyComponent::RigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass,btVector3& localInertia) : Component()
{
	collisionShape->calculateLocalInertia(mass, localInertia);

	//RIGIDBODY
	btRigidBody::btRigidBodyConstructionInfo RBInfo(mass, motionState, collisionShape, localInertia);
	rigidBody = new btRigidBody(RBInfo);
}


RigidbodyComponent::~RigidbodyComponent()
{
	delete rigidBody;
}


void RigidbodyComponent::start()
{
	//Añadimos al mundo
	TutorialApplication::getInstance()->getPhysicsEngine()->getDynamicsWorld()->addRigidBody(rigidBody);
}


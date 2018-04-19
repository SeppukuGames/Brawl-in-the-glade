#include "DynamicRigidbodyComponent.h"
#include "GameObject.h"

#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "TutorialApplication.h"

DynamicRigidbodyComponent::DynamicRigidbodyComponent(btMotionState *motionState, btCollisionShape *collisionShape, btScalar mass, btVector3& localInertia) 
	: RigidbodyComponent(motionState, collisionShape, mass, localInertia)
{
	TutorialApplication::getInstance()->getPhysicsEngine()->getCollisionShapes().push_back(collisionShape);

}


DynamicRigidbodyComponent::~DynamicRigidbodyComponent()
{
}

void DynamicRigidbodyComponent::start()
{
	rigidBody->setUserPointer(_gameObject->getNode());

	TutorialApplication::getInstance()->getPhysicsEngine()->getDynamicsWorld()->addRigidBody(rigidBody);
	TutorialApplication::getInstance()->getPhysicsEngine()->trackRigidBodyWithName(rigidBody, _gameObject->getNode()->getName());

}

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
	//En UserPointer metemos información que queremos utilizar para resolver las colisiones (GameObject)
	rigidBody->setUserPointer(_gameObject);

	TutorialApplication::getInstance()->getPhysicsEngine()->getDynamicsWorld()->addRigidBody(rigidBody);
	TutorialApplication::getInstance()->getPhysicsEngine()->trackRigidBodyWithName(rigidBody, _gameObject->getNode()->getName());
}

void DynamicRigidbodyComponent::tick(double elapsed){

	//Cogemos el transform del estado del rigidbody correspondiente
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);

	btQuaternion orientation = trans.getRotation();

	_gameObject->getNode()->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
	_gameObject->getNode()->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
}
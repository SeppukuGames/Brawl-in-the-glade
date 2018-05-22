#include "AttackComponent.h"


AttackComponent::AttackComponent()
{
}


AttackComponent::~AttackComponent()
{
}

//void MoveComponent::start() {
//	velocity = 50;
//	//direction = Ogre::Vector3::ZERO;
//	animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
//	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
//	direction = { 0, 0, 0 };
//	transform.setIdentity();
//};
//
//void MoveComponent::tick(double elapsed) {
//
//	//rb->getRigidbody()->setLinearVelocity(direction *2);
//
//	transform.setOrigin(transform.getOrigin() + direction * elapsed);
//	rb->getRigidbody()->setWorldTransform(transform);
//	rb->getRigidbody()->getMotionState()->setWorldTransform(transform);
//	rb->getRigidbody()->setLinearVelocity(btVector3(0, 0, 0));
//
//	//NO BORRAR, ÚTIL PARA DEBUG
//	//std::cout << "Direccion X: " << direction.getX() << "\n Direccion Z: " << direction.getZ() << std::endl;
//	/*std::cout << "Velocity X: " << rb->getRigidbody()->getLinearVelocity().getX() <<
//	"\n Velocity Y: " << rb->getRigidbody()->getLinearVelocity().getY() << "\n Velocity Z: " <<
//	rb->getRigidbody()->getLinearVelocity().getZ() << std::endl;
//	*/
//	//std::cout << "Rotation X: " << transform.getRotation().getX() << "\n Rotation Y: " << transform.getRotation().getY() << "\n Rotation Z: " << transform.getRotation().getZ() << std::endl;
//	//std::cout << "Transform X: " << transform.getOrigin().getX() << "\n Transform Y: " << transform.getOrigin().getY() << "\n Transform Z: " << transform.getOrigin().getZ() << std::endl;
//
//};
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "Error.h"
#include <Ogre.h>

RigidbodyComponent::RigidbodyComponent(bool kinematic, float density) :
kinematic(kinematic), density(density)
{
	
}

RigidbodyComponent::~RigidbodyComponent(){
}

void RigidbodyComponent::Start(){

	ColliderComponent * collider = (ColliderComponent*)(gameObject->GetComponent(COLLIDER));

	if (collider == nullptr){

		Error errorE("\n\n\n\n\nError al crear el Rigidbody. Necesita un Collider ");
		throw errorE;
	}

	body = collider->GetBody();

	if (!kinematic)
		body->SetType(b2BodyType::b2_dynamicBody);
	else
		body->SetType(b2BodyType::b2_kinematicBody);

	//TODO: meter más fixtures al body
	b2Fixture* fixture = body->GetFixtureList();
	fixture->SetDensity(density);

}

void RigidbodyComponent::Update(double elapsed){

	Ogre::SceneNode * node = gameObject->GetNode();
	b2Vec2 pos = body->GetPosition();
	float angle = body->GetAngle() + OFFSET;

	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(angle)), Ogre::Vector3(0, 0, 1));

	node->setPosition(Ogre::Vector3(pos.x, pos.y, 0));
	node->setOrientation(quat);
}

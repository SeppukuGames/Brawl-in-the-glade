#include "RigidbodyComponent.h"
#include "GameObject.h"

#include <Ogre.h>

RigidbodyComponent::RigidbodyComponent(bool kinematic, float density, float friction, float restitution) :
kinematic(kinematic), density(density), friction(friction), restitution(restitution)
{
	
}

RigidbodyComponent::~RigidbodyComponent(){
}

void RigidbodyComponent::Start(){
	//TODO: LANZAR EXCEPCION
	collider = (ColliderComponent*) (gameObject->GetComponent(COLLIDER));

	if (!kinematic)
		collider->GetBody()->SetType(b2BodyType::b2_dynamicBody);
	else
		collider->GetBody()->SetType(b2BodyType::b2_kinematicBody);

	//TODO: meter más fixtures al body
	b2Fixture fixture = collider->GetBody()->GetFixtureList()[0];
	fixture.SetDensity(density);
	fixture.SetFriction(friction);
	fixture.SetRestitution(restitution);
}

void RigidbodyComponent::Update(double elapsed){

	Ogre::SceneNode * node = gameObject->GetNode();
	b2Vec2 pos = collider->GetBody()->GetPosition();
	float angle = collider->GetBody()->GetAngle();

	Ogre::Radian angleRadians(angle / (2 * 3.14));
	Ogre::Quaternion quat;
	quat.FromAngleAxis(angleRadians, Ogre::Vector3(0, 1, 0));

	node->setPosition(Ogre::Vector3(pos.x, pos.y, 0));
	node->setOrientation(quat);
}

#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "Error.h"


RigidbodyComponent::RigidbodyComponent(bool kinematic, float density) :
kinematic(kinematic), density(density)
{

}

RigidbodyComponent::~RigidbodyComponent(){
}

void RigidbodyComponent::Start(){

	ColliderComponent * collider = (ColliderComponent*)(gameObject->GetComponent(COLLIDER));

	initialOrientation = gameObject->GetNode()->getOrientation();

	//Se lanza una excepcion en caso de intentar crear un rigidbody sin haber creado antes un collider
	if (collider == nullptr){

		Error errorE("\n\n\n\n\nError al crear el Rigidbody. Necesita un Collider ");
		throw errorE;
	}

	body = collider->GetBody();

	//Dependiendo de si es kinem�tico o no establecemos un tipo concreto
	if (!kinematic)
		body->SetType(b2BodyType::b2_dynamicBody);
	else
		body->SetType(b2BodyType::b2_kinematicBody);

	//Obtenemos la lista de Fixtures para establecer la densidad del objeto
	b2Fixture* fixture = body->GetFixtureList();
	fixture->SetDensity(density);

}

//M�todo que controla la posici�n y orientaci�n del objeto en cada frame
void RigidbodyComponent::Update(double elapsed){

	Ogre::SceneNode * node = gameObject->GetNode();

	//Obtenemos la posici�n y el �ngulo
	b2Vec2 pos = body->GetPosition();
	float angle = body->GetAngle() + OFFSET;

	//Convertimos el �ngulo en un quaternion para poder establecer la orientaci�n
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(angle)), Ogre::Vector3(0, 1, 0));

	//Establecemos la posici�n y orientaci�n correspondientes
	node->setPosition(Ogre::Vector3(pos.x, 0, pos.y));
	node->setOrientation(initialOrientation + quat);
}

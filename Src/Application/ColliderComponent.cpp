#include "ColliderComponent.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include <Ogre.h>

ColliderComponent::ColliderComponent(PhysicsMaterial material) : body(nullptr), pos(0, 0), angle(0), material(material)
{
}

ColliderComponent::~ColliderComponent(){
	body->GetWorld()->DestroyBody(body);
}

void ColliderComponent::Start(){
	//Obtenemos posición y rotación del nodo en el mundo para crear el cuerpo físico
	pos.Set(gameObject->GetNode()->getPosition().x, gameObject->GetNode()->getPosition().z);
	Ogre::Vector3 rotation = gameObject->GetNode()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	angle = rotation.z - OFFSET;

	CreateBody();

	b2Shape * shape = CreateShape();

	CreateFixture(shape);

	delete shape;
}

//Método encargado de crear un body del objeto
void ColliderComponent::CreateBody(){
	//1. Definir body
	b2BodyDef *bd = new b2BodyDef();
	bd->type = b2BodyType::b2_staticBody;
	bd->position.Set(pos.x, pos.y);
	bd->angle = angle;

	//2. Crear body
	body = PhysicsManager::GetInstance()->GetWorld()->CreateBody(bd);

	delete bd;

	//Guardamos el GameObject para poder detectar con quién colisiona
	body->SetUserData(gameObject);
}

//Método encargado de crear el fixture del objeto para asociarla al body
void ColliderComponent::CreateFixture(b2Shape* shape){

	//4. Crear Fixture
	b2FixtureDef *fd = new b2FixtureDef();
	fd->shape = shape;

	fd->density = DEFAULTDENSITY;
	fd->friction = material.friction;
	fd->restitution = material.restitution;

	//5. Adjuntar Shape al cuerpo con Fixture
	body->CreateFixture(fd);

	delete fd;
}

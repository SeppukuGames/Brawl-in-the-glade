#include "EntityComponent.h"

EntityComponent::EntityComponent(std::string meshString) : Component(){
	this->meshString = meshString;
}

EntityComponent::~EntityComponent()
{
	delete entity;
}

void EntityComponent::Start(){
	entity = gameObject->GetNode()->getCreator()->createEntity(meshString);		//Creamos la nueva entidad
	gameObject->SetObjMan(entity);												//Añadimos el gameObject al vector de Movable Objects
}


#include "EntityComponent.h"
#include "GameObject.h"

EntityComponent::EntityComponent(std::string meshString) : Component(){
	this->meshString = meshString;
}

EntityComponent::~EntityComponent()
{
	delete entity;
}

void EntityComponent::Start(){
	entity = gameObject->GetNode()->getCreator()->createEntity(meshString);
	gameObject->SetObjMan(entity);
}


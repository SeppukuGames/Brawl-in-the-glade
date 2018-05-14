#include "EntityComponent.h"

EntityComponent::EntityComponent(std::string meshString) : Component(){
	_meshString = meshString;

}

EntityComponent::~EntityComponent()
{
}

void EntityComponent::start(){
	_entity = _gameObject->getNode()->getCreator()->createEntity(_meshString);
	_gameObject->getNode()->attachObject(_entity);
}


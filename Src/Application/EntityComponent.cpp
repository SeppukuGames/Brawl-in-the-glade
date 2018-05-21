#include "EntityComponent.h"

EntityComponent::EntityComponent(std::string meshString, std::string entityName) : Component(){
	_meshString = meshString;
	_entityName = entityName;
}

EntityComponent::EntityComponent(std::string meshString) : Component(){
	_meshString = meshString;
}

EntityComponent::~EntityComponent()
{
	delete _entity;
}

void EntityComponent::start(){
	if (_entityName == "")
		_entity = _gameObject->getNode()->getCreator()->createEntity(_meshString);

	//He tocado aquí para crear una entidad a partir de un nombre
	else{
		_entity = _gameObject->getNode()->getCreator()->createEntity(_entityName, _meshString,Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME); 
	}


	_gameObject->getNode()->attachObject(_entity);
}


#ifndef ENTITYCOMPONENT_H_
#define ENTITYCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>
#include "GameObject.h"

class EntityComponent : public Component{
public:
	EntityComponent(std::string meshString) : Component()
	{
		_meshString = meshString;
		
	};
	virtual ~EntityComponent(){};

	virtual void start(){
		_entity = _gameObject->getNode()->getCreator()->createEntity(_meshString);
		_gameObject->getNode()->attachObject(_entity);
	};
	virtual void tick(double elapsed){

	};

	Ogre::Entity * getEntity()
	{
		return _entity;
	}

private:
	Ogre::Entity * _entity;
	std::string _meshString;
};

#endif /* RENDERCOMPONENT_H_ */
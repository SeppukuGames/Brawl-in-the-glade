#ifndef ENTITYCOMPONENT_H_
#define ENTITYCOMPONENT_H_

#include "Component.h"
#include "GameObject.h"
#include <OgreEntity.h>

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
	
	//CREAR EL GET ENTITY
	Ogre::Entity* getEntity(){
		return _entity;
	}

private:
	Ogre::Entity * _entity;
	std::string _meshString;
};

#endif /* RENDERCOMPONENT_H_ */
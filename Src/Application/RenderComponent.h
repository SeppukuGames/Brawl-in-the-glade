#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>

class RenderComponent : public Component{
public:
	RenderComponent(std::string meshString) : Component()
	{
		_meshString = meshString;
		
	};
	virtual ~RenderComponent(){};

	virtual void start(){
		_entity = _gameObject->getNode()->getCreator()->createEntity(_meshString);
		_gameObject->getNode()->attachObject(_entity);
	};
	virtual void tick(){

	};

	Ogre::Entity *GetEntity()
	{
		return _entity;
	}

private:
	Ogre::Entity * _entity;
	std::string _meshString;
};

#endif /* RENDERCOMPONENT_H_ */
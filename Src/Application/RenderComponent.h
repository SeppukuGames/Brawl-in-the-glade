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

private:
	Ogre::Entity * _entity;//Para el renderizado
	std::string _meshString;
};

#endif /* RENDERCOMPONENT_H_ */
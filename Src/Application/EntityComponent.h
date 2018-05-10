#ifndef ENTITYCOMPONENT_H_
#define ENTITYCOMPONENT_H_

#include "Component.h"
#include "GameObject.h"
#include <OgreEntity.h>

class EntityComponent : public Component{

//-----------------------------------ATRIBUTOS-------------------------
private:
	Ogre::Entity * _entity;
	std::string _meshString;

//-----------------------------------ATRIBUTOS-------------------------

//-----------------------------------M�TODOS----------------------------
public:
	EntityComponent(std::string meshString);

	virtual ~EntityComponent();

	virtual void start();

	inline Ogre::Entity* getEntity(){return _entity;}

//-----------------------------------M�TODOS----------------------------

};

#endif /* ENTITYCOMPONENT_H_ */
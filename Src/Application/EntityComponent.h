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
	std::string _entityName;//nombre de la entidad (en el caso en el que tenga)

	//-----------------------------------ATRIBUTOS-------------------------

	//-----------------------------------MÉTODOS----------------------------
public:
	EntityComponent(std::string meshString, std::string entityName);

	EntityComponent(std::string meshString);


	virtual ~EntityComponent();

	virtual void start();

	inline Ogre::Entity* getEntity(){ return _entity; }

	//-----------------------------------MÉTODOS----------------------------

};

#endif /* ENTITYCOMPONENT_H_ */
#ifndef __EntityComponent_h_
#define __EntityComponent_h_

#include "Component.h"
#include <Ogre.h>


class EntityComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Entity * entity;				//Atributos para establecer la entidad a crear y el nombre del mesh del GameObject

	std::string meshString;

#pragma endregion Attributes

#pragma region Methods  
public:
	EntityComponent(std::string meshString);

	virtual ~EntityComponent();

	virtual void Start();

	inline Ogre::Entity* GetEntity(){ return entity; }		//Método utilizado para obtener la entidad

#pragma endregion Methods

};

#endif /* __EntityComponent_h_ */
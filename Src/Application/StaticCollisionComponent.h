#ifndef STATICCOLLISIONCOMPONENT_H_
#define STATICCOLLISIONCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>
#include "EntityComponent.h"
#include <iostream>


class StaticCollisionComponent : public Component{
public:
	StaticCollisionComponent(EntityComponent* entComponent) : Component()
	{
		entityComponent = entComponent;

	};
	virtual ~StaticCollisionComponent(){};

	virtual void start();

	virtual void tick(double elapsed);

	Ogre::AxisAlignedBox getBoundingBox()
	{
		return  entityComponent->getEntity()->getWorldBoundingBox();
	}


protected:
	int contador;
	EntityComponent* entityComponent;

};

#endif /* STATICCOLLISIONCOMPONENT_H_ */
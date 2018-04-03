#ifndef COLLISIONCOMPONENT_H_
#define COLLISIONCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>
#include "EntityComponent.h"
#include "NewMOC.h"
#include "TutorialApplication.h"

class CollisionComponent : public Component{
public:
	CollisionComponent(EntityComponent* entComponent) : Component()
	{
		entityComponent = entComponent;

	};
	virtual ~CollisionComponent(){};

	virtual void start(){
		collisionManager = TutorialApplication::getInstance()->getCollisionManager();
		collisionManager->register_entity(entityComponent->getEntity(), Collision::COLLISION_BOX);


	};
	virtual void tick(double elapsed){

	};

private:
	EntityComponent* entityComponent;
	Collision::CollisionTools* collisionManager;
};

#endif /* RENDERCOMPONENT_H_ */
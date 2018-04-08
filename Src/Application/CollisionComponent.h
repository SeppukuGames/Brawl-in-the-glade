#ifndef COLLISIONCOMPONENT_H_
#define COLLISIONCOMPONENT_H_

#include "StaticCollisionComponent.h"


class CollisionComponent : public StaticCollisionComponent{
public:
	CollisionComponent(EntityComponent* entComponent) : StaticCollisionComponent(entComponent)
	{

	};
	virtual ~CollisionComponent(){};

	virtual void tick(double elapsed);


};

#endif /* RENDERCOMPONENT_H_ */
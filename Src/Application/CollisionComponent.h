#ifndef COLLISIONCOMPONENT_H_
#define COLLISIONCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>

class CollisionComponent : public Component{
public:
	CollisionComponent() : Component()
	{


	};
	virtual ~CollisionComponent(){};

	virtual void start(){


	};
	virtual void tick(double elapsed){

	};

private:
	
};

#endif /* RENDERCOMPONENT_H_ */
#ifndef A_H_
#define A_H_

#include <vector>
#include "StaticCollisionComponent.h"

class CollisionManager
{
public:

	void registerCollisionComponent(StaticCollisionComponent*c){ collisionGameObjects.push_back(c); }
	std::vector <StaticCollisionComponent*> getCollisionGameObjects(){ return collisionGameObjects; }

	CollisionManager() : collisionGameObjects(0)
	{


	}

private:
	std::vector <StaticCollisionComponent*> collisionGameObjects;

};
#endif /* RENDERCOMPONENT_H_ */
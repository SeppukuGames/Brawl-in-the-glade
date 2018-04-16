#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

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
#endif /* COLLISIONMANAGER_H_ */
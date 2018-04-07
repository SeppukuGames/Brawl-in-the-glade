#ifndef COLLISIONCOMPONENT_H_
#define COLLISIONCOMPONENT_H_

#include "Component.h"
#include <OgreEntity.h>
#include "EntityComponent.h"
#include "NewMOC.h"
#include "TutorialApplication.h"
#include <iostream>

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
		_gameObject->getNode()->showBoundingBox(true);
		boxSize = entityComponent->getEntity()->getBoundingBox().getSize();
	};
	virtual void tick(double elapsed){
	
		Ogre::Ray ray(_gameObject->getNode()->getPosition(),Ogre::Vector3(0,0,1));
		
		Ogre::Real x, y, z;
		x = _gameObject->getNode()->getPosition().x;
		y = _gameObject->getNode()->getPosition().y;
		z = _gameObject->getNode()->getPosition().z;

		
		Ogre::Vector3 origen = Ogre::Vector3(x, y, z + boxSize.z/2);
		Ogre::Vector3 direccion = Ogre::Vector3(x, y, z + boxSize.z *20);

		//Collision::SCheckCollisionAnswer ret = collisionManager->check_ray_collision(entityComponent->getEntity()->getBoundingBox()., Ogre::uint32(42496729U), entityComponent->getEntity(), boxSize.z / 2);
		Collision::SCheckCollisionAnswer ret = collisionManager->check_ray_collision(origen, direccion, 100000000,0);


		// check if we found collision:
		if (ret.collided)
		{
			std::cout << _gameObject->getNode()->getOrientation();
		}
		
	};

private:
	EntityComponent* entityComponent;
	Collision::CollisionTools* collisionManager;

	Ogre::Vector3 boxSize;
};

#endif /* RENDERCOMPONENT_H_ */
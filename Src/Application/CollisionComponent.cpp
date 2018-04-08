#include "CollisionComponent.h"
#include "Header.h"
#include "TutorialApplication.h"

void CollisionComponent::tick(double elapsed){

	contador++;
	if (contador == 20)
	{
		Ogre::AxisAlignedBox box = getBoundingBox();

		for (int i = 0; i < TutorialApplication::getInstance()->getCollisionManager()->getCollisionGameObjects().size(); i++)
		{
			if (TutorialApplication::getInstance()->getCollisionManager()->getCollisionGameObjects()[i] != this)
			{
				Ogre::AxisAlignedBox otherBox = TutorialApplication::getInstance()->getCollisionManager()->getCollisionGameObjects()[i]->getBoundingBox();

				if (box.intersects(otherBox))
				{
					Ogre::AxisAlignedBox intersectionBox = box.intersection(otherBox);
					std::cout << intersectionBox << '\n';

					//std::cout << boundingBox << '\n';

					//std::cout << TutorialApplication::getInstance()->getCollisionManager()->getCollisionGameObjects()[i]->getBoundingBox() << '\n';
				}
			}

		}
		contador = 0;
	}
	

};
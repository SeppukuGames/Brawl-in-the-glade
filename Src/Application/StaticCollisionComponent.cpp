#include "StaticCollisionComponent.h"
#include "Header.h"
#include "TutorialApplication.h"

void StaticCollisionComponent::start(){

	//_gameObject->getNode()->showBoundingBox(true);
	TutorialApplication::getInstance()->getCollisionManager()->registerCollisionComponent(this);
	contador = 0;
};

void StaticCollisionComponent::tick(double elapsed){};
#include "StaticCollisionComponent.h"
#include "CollisionManager.h"
#include "TutorialApplication.h"
#include "GameObject.h"

void StaticCollisionComponent::start(){
	entityComponent = dynamic_cast<EntityComponent*> (_gameObject->getComponent(ComponentName::ENTITY));

	//_gameObject->getNode()->showBoundingBox(true);
	TutorialApplication::getInstance()->getCollisionManager()->registerCollisionComponent(this);
	contador = 0;
};

void StaticCollisionComponent::tick(double elapsed){};
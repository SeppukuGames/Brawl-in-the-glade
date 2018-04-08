#include "GameComponent.h"
#include "EntityComponent.h"
#include "KeyInputComponent.h"
#include "StaticCollisionComponent.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"

GameComponent::GameComponent(Ogre::SceneManager * mSceneMgr) : GameObject(mSceneMgr),
components(0){}

GameComponent::~GameComponent() {
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void GameComponent::tick(double elapsed) {
	for (int i = 0; i < components.size(); i++)
		components[i]->tick(elapsed);

}


void GameComponent::addComponent(Component* comp) {
	comp->setGameObject(this);
	comp->start();
	components.push_back(comp);
}

Component* GameComponent::getComponent(ComponentName component) {

	switch (component)
	{
	case ComponentName::COLLISION:
		for (int i = 0; i < components.size(); i++)
		{
			CollisionComponent* comp = dynamic_cast<CollisionComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::ENTITY:
		for (int i = 0; i < components.size(); i++)
		{
			EntityComponent* comp = dynamic_cast<EntityComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::STATICCOLLISION:
		for (int i = 0; i < components.size(); i++)
		{
			StaticCollisionComponent* comp = dynamic_cast<StaticCollisionComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::KEYINPUT:
		for (int i = 0; i < components.size(); i++)
		{
			KeyInputComponent* comp = dynamic_cast<KeyInputComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::MOVE:
		for (int i = 0; i < components.size(); i++)
		{
			MoveComponent* comp = dynamic_cast<MoveComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;
	}

}
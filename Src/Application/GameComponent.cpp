#include "GameComponent.h"

GameComponent::GameComponent(Ogre::SceneNode* scnNode) : GameObject(scnNode),
components(0){}

GameComponent::~GameComponent() {
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void GameComponent::tick() {
	for (int i = 0; i < components.size(); i++)
		components[i]->tick();

}


void GameComponent::addComponent(Component* comp) {
	comp->setGameObject(this);
	comp->start();
	components.push_back(comp);
}
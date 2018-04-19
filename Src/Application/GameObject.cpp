#include "GameObject.h"
#include <OgreMovableObject.h>

#include "EntityComponent.h"
#include "KeyInputComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"

GameObject::GameObject(Ogre::SceneManager * mSceneMgr)  :components(0){
	control = new UserControl(this);
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
}


GameObject::~GameObject() {
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}

	UserControl* pCtrl = Ogre::any_cast<UserControl*>(
		node->getAttachedObject(0)->//Suponemos que solo puede tener controlador el primer objeto adjunto a un nodo
		getUserObjectBindings().getUserAny());
	delete pCtrl;
}

void GameObject::setObjMan(Ogre::MovableObject* mObj) {
	//comprobar que es primer objeto que se adjunta al nodo
	if (node->numAttachedObjects() == 0)
	{
		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
	}
	//else a lo mejor hay que hacer algo (DESCONOZCO SI ESTA BIEN)
	else
	{
		node->detachAllObjects();
		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
	}
}




void GameObject::tick(double elapsed) {
	for (size_t i = 0; i < components.size(); i++)
		components[i]->tick(elapsed);

}


void GameObject::addComponent(Component* comp) {
	comp->setGameObject(this);
	comp->start();
	components.push_back(comp);
}

Component* GameObject::getComponent(ComponentName component) {

	switch (component)
	{

	case ComponentName::ENTITY:
		for (size_t i = 0; i < components.size(); i++)
		{
			EntityComponent* comp = dynamic_cast<EntityComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::KEYINPUT:
		for (size_t i = 0; i < components.size(); i++)
		{
			KeyInputComponent* comp = dynamic_cast<KeyInputComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::MOVE:
		for (size_t i = 0; i < components.size(); i++)
		{
			MoveComponent* comp = dynamic_cast<MoveComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::ANIMATION:
		for (size_t i = 0; i < components.size(); i++)
		{
			AnimationComponent* comp = dynamic_cast<AnimationComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;
	}

	return NULL;

}
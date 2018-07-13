#include "GameObject.h"
#include <OgreMovableObject.h>

#include "EntityComponent.h"
#include "KeyInputComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "MoveCameraComponent.h"
#include "TestCollisionComponent2.h"
#include "Enemigo.h"
#include "UICanvas.h"
#include "PlayerComponent.h"
#include "TowerComponent.h"
#include "MouseComponent.h"
#include "MenuGameOver.h"
#include "MenuPausa.h"
#include "MenuPrincipal.h"
#include "MainGame.h"
#include "PanelOleada.h"

GameObject::GameObject(Ogre::SceneManager * mSceneMgr, std::string name) :components(0){
	control = new UserControl(this);
	if (name != ""){
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0, 0, 0));
		std::cout << name << std::endl;
	}
	else
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));

}


GameObject::~GameObject() {
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}

	
	//UserControl* pCtrl = Ogre::any_cast<UserControl*>(
	//	node->getAttachedObject(0)->//Suponemos que solo puede tener controlador el primer objeto adjunto a un nodo
	//	getUserObjectBindings().getUserAny());

	//unsigned int  = 0;
	//node->detachObject(hola);
	//delete pCtrl;
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

	case ComponentName::MOVE_CAMERA:
		for (size_t i = 0; i < components.size(); i++)
		{
			MoveCameraComponent* comp = dynamic_cast<MoveCameraComponent*> (components[i]);

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

	case ComponentName::RIGIDBODY:
		for (size_t i = 0; i < components.size(); i++)
		{
			DynamicRigidbodyComponent* comp = dynamic_cast<DynamicRigidbodyComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;
	

	case ComponentName::TESTCOLLISIONCOMPONENT2:
		for (size_t i = 0; i < components.size(); i++)
		{
			TestCollisionComponent2* comp = dynamic_cast<TestCollisionComponent2*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::ENEMY:
		for (size_t i = 0; i < components.size(); i++)
		{
			Enemigo* comp = dynamic_cast<Enemigo*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::UI:
		for (size_t i = 0; i < components.size(); i++)
		{
			UICanvas* comp = dynamic_cast<UICanvas*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::PLAYER:
		for (size_t i = 0; i < components.size(); i++)
		{
			PlayerComponent* comp = dynamic_cast<PlayerComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::TOWER:
		for (size_t i = 0; i < components.size(); i++)
		{
			TowerComponent* comp = dynamic_cast<TowerComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::MOUSE:
		for (size_t i = 0; i < components.size(); i++)
		{
			MouseComponent* comp = dynamic_cast<MouseComponent*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::MENUPAUSA:
		for (size_t i = 0; i < components.size(); i++)
		{
			MenuPausa* comp = dynamic_cast<MenuPausa*> (components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;

	case ComponentName::MENUGAMEOVER:
		for (size_t i = 0; i < components.size(); i++)
		{
			MenuGameOver* comp = dynamic_cast<MenuGameOver*> (components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;

	case ComponentName::MENUPRINCIPAL:
		for (size_t i = 0; i < components.size(); i++)
		{
			MenuPrincipal* comp = dynamic_cast<MenuPrincipal*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;

	case ComponentName::MAINGAME:
		for (size_t i = 0; i < components.size(); i++)
		{
			MainGame* comp = dynamic_cast<MainGame*> (components[i]);

			if (comp != NULL)
				return components[i];
		}
		break;
	
	case ComponentName::PANELOLEADA:
		for (size_t i = 0; i < components.size(); i++)
		{
			PanelOleada* comp = dynamic_cast<PanelOleada*> (components[i]);

			if (comp != NULL)
				return components[i];

		}

		break;
	}

	

	return NULL;

}

void GameObject::onCollision(GameObject *collision){

	for (size_t i = 0; i < components.size(); i++)
		components[i]->onCollision(collision);
}

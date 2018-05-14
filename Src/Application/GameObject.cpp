#include "GameObject.h"
#include <OgreMovableObject.h>

#include "EntityComponent.h"
#include "KeyInputComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "MoveCameraComponent.h"
#include "MouseComponent.h"

GameObject::GameObject(Ogre::SceneManager * mSceneMgr, std::string name) :components(0){
	control = new UserControl(this);
	if (name != "")
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(name,Ogre::Vector3(0, 0, 0));
	else
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

    case ComponentName::MOUSE:
        for (size_t i = 0; i < components.size(); i++)
        {
            MouseComponent* comp = dynamic_cast<MouseComponent*> (components[i]);

            if (comp != NULL)
                return components[i];

        }

        break;
	}

	return NULL;

}

void GameObject::pushMensaje(Mensaje* msj) {
	recibidos.push_back(msj);
}

//Vuelca los mensajes del recieved al deliver para mandarlos en el siguiente tick.
void GameObject::vuelcaMensajes() {

	while (!recibidos.empty()) {
		Mensaje* msj = recibidos.front();
		recibidos.pop_front();
		//metemos el mensaje al deliver para mandarlo
		deliver.push_back(msj);
	}
}

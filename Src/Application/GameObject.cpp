#include "GameObject.h"
#include "EntityComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

GameObject::GameObject(Ogre::SceneManager * mSceneMgr, std::string name) :components(0), name(name){
	control = new UserControl(this);
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0, 0, 0));
}

GameObject::~GameObject() 
{
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}

	//TODO: HIJOS

	//UserControl* pCtrl = Ogre::any_cast<UserControl*>(
	//	node->getAttachedObject(0)->//Suponemos que solo puede tener controlador el primer objeto adjunto a un nodo
	//	getUserObjectBindings().getUserAny());

	//unsigned int  = 0;
	//node->detachObject(hola);
	//delete pCtrl;
}

void GameObject::Tick(double elapsed) {
	size_t i = 0;
	while (!components.empty() && i < components.size()){
		components[i]->Update(elapsed);
		i++;
	}
}

void GameObject::AddComponent(Component* comp) {
	components.push_back(comp);
	comp->SetGameObject(this);
	comp->Start();
}

Component* GameObject::GetComponent(ComponentName component) {

	switch (component)
	{
	case ComponentName::ENTITY:
		for (size_t i = 0; i < components.size(); i++)
		{
			EntityComponent* comp = dynamic_cast<EntityComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::COLLIDER:
		for (size_t i = 0; i < components.size(); i++)
		{
			ColliderComponent* comp = dynamic_cast<ColliderComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::BOXCOLLIDER:
		for (size_t i = 0; i < components.size(); i++)
		{
			BoxColliderComponent* comp = dynamic_cast<BoxColliderComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::RIGIDBODY:
		for (size_t i = 0; i < components.size(); i++)
		{
			RigidbodyComponent* comp = dynamic_cast<RigidbodyComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	}

	return NULL;
}

//Es llamado cuando dos gameObject colisionan. Informa a todos sus componentes
void GameObject::OnCollisionEnter(ColliderComponent* collider){
	for (size_t i = 0; i < components.size(); i++)
		components[i]->OnCollisionEnter(collider);
}

//Es llamado cuando dos gameObject dejan de colisionar. Informa a todos sus componentes
void GameObject::OnCollisionExit(ColliderComponent* collider){
	for (size_t i = 0; i < components.size(); i++)
		components[i]->OnCollisionExit(collider);
}


void GameObject::SetObjMan(Ogre::MovableObject* mObj) {
	//comprobar que es primer objeto que se adjunta al nodo
	if (node->numAttachedObjects() == 0)
	{
		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
	}
	else
	{
		node->detachAllObjects();
		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
	}
}

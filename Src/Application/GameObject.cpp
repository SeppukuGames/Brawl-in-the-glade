#include "GameObject.h"

GameObject::GameObject(Ogre::SceneManager * mSceneMgr, std::string name) :components(0){
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

void GameObject::SetObjMan(Ogre::MovableObject* mObj) {
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


void GameObject::Tick(double elapsed) {
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Update(elapsed);

}


void GameObject::AddComponent(Component* comp) {
	components.push_back(comp);
	comp->SetGameObject(this);
	comp->Start();
}

Component* GameObject::GetComponent(ComponentName component) {

	//switch (component)
	//{
	//case ComponentName::ENTITY:
	//	for (size_t i = 0; i < components.size(); i++)
	//	{
	//		EntityComponent* comp = dynamic_cast<EntityComponent*> (components[i]);

	//		if (comp != NULL)
	//			return components[i];

	//	}

	//	break;
	//}

	return NULL;
}

//void GameObject::onCollision(GameObject *collision){
//
//	for (size_t i = 0; i < components.size(); i++)
//		components[i]->onCollision(collision);
//}

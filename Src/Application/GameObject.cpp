#include "GameObject.h"

#include <OgreMovableObject.h>

GameObject::GameObject(Ogre::SceneManager * mSceneMgr) {
	control = new UserControl(this);
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
}


GameObject::~GameObject() {
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
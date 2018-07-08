#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "Component.h"

class GameObject; // declaración adelantada

class UserControl { // clase recubridora
public:
	GameObject* getControl() { return object; };
	friend class GameObject;
protected:
	UserControl(GameObject * obj) : object(obj) { };
	~UserControl() { };
	GameObject * object; // ObjectMan: clase raíz de una jerarquía
};

class GameObject
{
public:
	GameObject(Ogre::SceneManager * mSceneMgr, std::string name = "");
	virtual ~GameObject();

	virtual void Tick(double elapsed);

	virtual void AddComponent(Component* comp);
	virtual Component* GetComponent(ComponentName component);

	virtual void SetObjMan(Ogre::MovableObject* mObj);
	inline Ogre::SceneNode* GetNode(){ return node; };

protected:

	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;

	std::vector<Component*> components;
};
#endif

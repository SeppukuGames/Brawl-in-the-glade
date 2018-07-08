#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "Component.h"

class GameObject; // declaraci�n adelantada

class UserControl { // clase recubridora
public:
	GameObject* getControl() { return object; };
	friend class GameObject;
protected:
	UserControl(GameObject * obj) : object(obj) { };
	~UserControl() { };
	GameObject * object; // ObjectMan: clase ra�z de una jerarqu�a
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

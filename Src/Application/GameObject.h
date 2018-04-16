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
	/*
	//Flags para click del rat�n
	static const Ogre::uint32 MY_QUERY_MASK = 1; // << 0; //Lo tienen todos los objetos que quiero procesar
	static const Ogre::uint32 O_QUERY_MASK = 0;
	*/
	GameObject(Ogre::SceneManager * mSceneMgr);

	virtual void addComponent(Component* comp);
	virtual Component* getComponent(ComponentName component);


	// from GameObject
	virtual void tick(double elapsed);


	virtual void setObjMan(Ogre::MovableObject* mObj);

	virtual ~GameObject();

	inline Ogre::SceneNode* getNode(){ return node; };

protected:

	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;

	std::vector<Component*> components;


	//UN PUNTERO AL GAME/ GAMEMANAGER?
};

#endif

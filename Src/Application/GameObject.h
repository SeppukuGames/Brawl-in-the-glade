#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>

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

	virtual void tick() = 0;

	virtual void setObjMan(Ogre::MovableObject* mObj);

	virtual ~GameObject();

	inline Ogre::SceneNode* getNode(){ return node; };

protected:
	GameObject(Ogre::SceneNode* scnNode);

	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;


	//UN PUNTERO AL GAME/ GAMEMANAGER?
};

#endif

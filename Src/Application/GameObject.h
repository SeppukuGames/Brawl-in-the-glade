#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "Component.h"
#include "Mensaje.h"
#include <list>

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
	/*
	//Flags para click del ratón
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


	void pushMensaje(Mensaje* msj);	//Pushea un mensaje a los recibidos
	virtual void leeMensajes() {};	//Cada componente va a definir en funcion de los mensajes que quiera leer

									//Vuelca los mensajes del recieved al deliver para mandarlos en el siguiente tick.
	void vuelcaMensajes();

protected:

	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;

	std::vector<Component*> components;

	/*
	La lista delivered es para hacer el delivery en un tick y enviar los mensajes a los componentes.
	La segunda lista, recibidos, es donde guardamos los mensajes generados en ese tick -por los componentes- que se la pasamos
	a delivered al final del tick para que la lean al siguiente tick.
	*/
	std::list <Mensaje*> deliver;			//Mensajes que envias
	std::list <Mensaje*> recibidos;			//ROGER ROGER	//Mensajes que recibes de los componentes

	//UN PUNTERO AL GAME/ GAMEMANAGER?
};

#endif

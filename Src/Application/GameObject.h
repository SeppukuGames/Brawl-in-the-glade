#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include "Component.h"
#include "ColliderComponent.h"

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
	GameObject(std::string name);
	~GameObject();

	void Tick(double elapsed);

	void AddComponent(Component* comp);									//M�todo encargado de a�adir un componente
	Component* GetComponent(ComponentName component);					//M�todo que devuelve un componente espec�fico

	void OnCollisionEnter(ColliderComponent* collider);					//Es llamado cuando dos gameObject colisionan. Informa a todos sus componentes
	void OnCollisionExit(ColliderComponent* collider);					//Es llamado cuando dos gameObject dejan de colisionar. Informa a todos sus componentes

	void SetObjMan(Ogre::MovableObject* mObj);							//M�todo que a�ade al vector de Movable Objects un nuevo elemento

	inline Ogre::SceneNode* GetNode(){ return node; };					//M�todo que devuelve el nodo
		
	inline std::string GetTag(){ return tag; };						//M�todo que devuelve el tag del nodo
	inline void SetTag(std::string tag){ this->tag = tag; };		//M�todo que establece el tag del nodo

protected:
	Ogre::SceneNode* node = nullptr;									//Atributo para la referencia al nodo
	UserControl* control = nullptr;										//Atributo para la referencia al UserControl
	std::string tag = "default";										//Atributo para establecer el tag del nodo
	std::vector<Component*> components;									//Vector de componentes
};
#endif

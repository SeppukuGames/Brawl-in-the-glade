#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include "Component.h"
#include "ColliderComponent.h"

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
	GameObject(std::string name);
	~GameObject();

	void Tick(double elapsed);

	void AddComponent(Component* comp);									//Método encargado de añadir un componente
	Component* GetComponent(ComponentName component);					//Método que devuelve un componente específico

	void OnCollisionEnter(ColliderComponent* collider);					//Es llamado cuando dos gameObject colisionan. Informa a todos sus componentes
	void OnCollisionExit(ColliderComponent* collider);					//Es llamado cuando dos gameObject dejan de colisionar. Informa a todos sus componentes

	void SetObjMan(Ogre::MovableObject* mObj);							//Método que añade al vector de Movable Objects un nuevo elemento

	inline Ogre::SceneNode* GetNode(){ return node; };					//Método que devuelve el nodo
		
	inline std::string GetTag(){ return tag; };						//Método que devuelve el tag del nodo
	inline void SetTag(std::string tag){ this->tag = tag; };		//Método que establece el tag del nodo

protected:
	Ogre::SceneNode* node = nullptr;									//Atributo para la referencia al nodo
	UserControl* control = nullptr;										//Atributo para la referencia al UserControl
	std::string tag = "default";										//Atributo para establecer el tag del nodo
	std::vector<Component*> components;									//Vector de componentes
};
#endif

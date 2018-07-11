#ifndef __GameObject_H__
#define __GameObject_H__

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
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
	GameObject(Ogre::SceneManager * mSceneMgr, std::string name = "");
	~GameObject();

	void Tick(double elapsed);

	void AddComponent(Component* comp);
	Component* GetComponent(ComponentName component);

	void OnCollisionEnter(ColliderComponent* collider);		//Es llamado cuando dos gameObject colisionan. Informa a todos sus componentes
	void OnCollisionExit(ColliderComponent* collider);		//Es llamado cuando dos gameObject dejan de colisionar. Informa a todos sus componentes

	void SetObjMan(Ogre::MovableObject* mObj);

	inline Ogre::SceneNode* GetNode(){ return node; };
	inline std::string GetName(){ return name; };

	inline std::string GetTag(){ return name; };
	inline std::string SetTag(std::string tag){ this->tag = tag; };

protected:
	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;
	std::string name;
	std::string tag = "default";
	//TODO: TRANSFORM
	std::vector<Component*> components;
};
#endif

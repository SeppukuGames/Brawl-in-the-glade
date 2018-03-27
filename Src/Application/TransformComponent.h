#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "Component.h"
#include <OgreSceneNode.h>

class TransformComponent : public Component{
public:
	TransformComponent() : Component()
	{}
	virtual ~TransformComponent(){}

	virtual void start(){ 
		_nodo = _gameObject->getNode();
		_nodo->setPosition(0, 0, 0);
	}
	virtual void tick(){}

	void SetPosition(Ogre::Vector3 aux){ _nodo->setPosition(aux); }
	void SetPosition(int x, int y, int z){ _nodo->setPosition(x, y, z); }
	void SetScale(Ogre::Vector3 aux){ _nodo->scale(aux); }

	void SetRotation(Ogre::Vector3 aux, int grados){ _nodo->rotate(aux, Ogre::Degree(grados)); }

private:

	Ogre::SceneNode* _nodo;

};

#endif /* TRANSFORMCOMPONENT_H_ */
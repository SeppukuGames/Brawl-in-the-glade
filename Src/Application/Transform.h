#pragma once
#include "Component.h"

class Transform : public Component{
public:
	Transform(Ogre::Vector3 vector) : Component()
	{
		aux = vector;
	};
	virtual ~Transform(){};

	virtual void start(){ _gameObject->getNode()->setPosition(aux); };
	virtual void tick(){};

private:
	Ogre::Vector3 aux;
};

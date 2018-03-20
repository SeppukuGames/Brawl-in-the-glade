#pragma once
#include "Component.h"

class componenteEscalado : public Component{
public:
	componenteEscalado(Ogre::Vector3 vector) : Component()
	{
		aux = vector;		
	};
	virtual ~componenteEscalado(){};

	virtual void start(){ _gameObject->getNode()->setScale(aux); };
	virtual void tick(){};

private:	
	Ogre::Vector3 aux;
};

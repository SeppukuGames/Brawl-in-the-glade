#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "Component.h"

class OgritoRotaComponent : public Component{
public:
	OgritoRotaComponent() : Component()
	{};
	virtual ~OgritoRotaComponent(){};

	virtual void start(){ rotation = 0; };
	virtual void tick(){
		rotation += 0.01;
		_gameObject->getNode()->setScale(Ogre::Vector3(rotation, rotation, rotation));

	};

private: 
	float rotation;
};

#endif /* INPUTCOMPONENT_H_ */
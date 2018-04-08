#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "GameObject.h"

enum ComponentName{ COLLISION, ENTITY, MOVE, KEYINPUT, STATICCOLLISION };

class Component {
public:
	Component() : _gameObject(nullptr)
	{};
	virtual ~Component(){};

	virtual void start() = 0;
	virtual void tick(double elapsed) = 0;

	inline void setGameObject(GameObject * gameObject){ _gameObject = gameObject; };

protected:
	GameObject * _gameObject;
};

#endif /* _COMPONENT_H_*/
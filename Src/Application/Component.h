#ifndef _COMPONENT_H_
#define _COMPONENT_H_

//Declaración adelantada para evitar ciclo de inclusiones
class GameObject;

enum ComponentName{ COLLISION, ENTITY, MOVE, KEYINPUT, STATICCOLLISION, ANIMATION, RIGIDBODY, MOVE_CAMERA, MOUSE};

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
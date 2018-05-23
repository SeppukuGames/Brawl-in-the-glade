#ifndef _COMPONENT_H_
#define _COMPONENT_H_

//Declaración adelantada para evitar ciclo de inclusiones
class GameObject;

enum ComponentName{ COLLISION, ENTITY, MOVE, KEYINPUT, STATICCOLLISION, ANIMATION, RIGIDBODY, MOVE_CAMERA, TESTCOLLISIONCOMPONENT2, ENEMY, UI, PLAYER, TOWER, MOUSE, MENUPAUSA, MENUGAMEOVER, MENUPRINCIPAL, MAINGAME };

class Component {
public:
	Component() : _gameObject(nullptr)
	{};
	virtual ~Component(){};

	virtual void start() {};
	virtual void tick(double elapsed) {};
	virtual void onCollision(GameObject *collision){};

	inline void setGameObject(GameObject * gameObject){ _gameObject = gameObject; };

protected:
	GameObject * _gameObject;
};

#endif /* _COMPONENT_H_*/
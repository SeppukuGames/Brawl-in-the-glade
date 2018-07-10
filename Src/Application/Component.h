#ifndef __Component_h_
#define __Component_h_

//Declaración adelantada para evitar ciclo de inclusiones
class GameObject;

//TODO: Meter los que se usen
enum ComponentName{
	ENTITY, COLLIDER, BOXCOLLIDER, RIGIDBODY
};

class Component
{
public:
	Component() : gameObject(nullptr){};
	virtual ~Component(){};

	virtual void Start() {};
	virtual void Update(double elapsed) {};
	//virtual void OnCollision(GameObject *collision){};

	inline void SetGameObject(GameObject * gameObject){ this->gameObject = gameObject; };

protected:
	GameObject * gameObject;
};
#endif // #ifndef __Component_h_


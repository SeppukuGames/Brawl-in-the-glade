#ifndef __Component_h_
#define __Component_h_


//Declaración adelantada para evitar ciclo de inclusiones
class GameObject;
class ColliderComponent;

//TODO: Meter los que se usen
enum ComponentName{
	ENTITY, COLLIDER, BOXCOLLIDER, CIRCLECOLLIDER, RIGIDBODY, AUDIO, LIGHT, CAMERA, GAMEMANAGER, PAUSEMANAGER
};

class Component
{
public:
	Component() : gameObject(nullptr){};
	virtual ~Component(){};

	virtual void Start() {};
	virtual void Update(double elapsed) {};

	virtual void OnCollisionEnter(ColliderComponent* collider){};		//Es llamado cuando dos gameObject colisionan.
	virtual void OnCollisionExit(ColliderComponent* collider){};		//Es llamado cuando dos gameObject dejan de colisionar. 

	inline GameObject * GetGameObject(){ return gameObject; };
	inline void SetGameObject(GameObject * gameObject){ this->gameObject = gameObject; };

protected:
	GameObject * gameObject;
};
#endif // #ifndef __Component_h_


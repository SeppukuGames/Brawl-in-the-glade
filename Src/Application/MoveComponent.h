#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "PlayerComponent.h"
#include "MouseComponent.h"


class MoveComponent : public KeyInputComponent {
public:

	MoveComponent() : KeyInputComponent()
	{

	};
	virtual ~MoveComponent() {};

	virtual void start();
	virtual void tick(double elapsed);
	virtual void onCollision(GameObject *);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	//btVector3 direction;
	
private:
	//Ogre::Vector3 direction; 
	float velocity;
	btVector3 direction, oldDirection;
	DynamicRigidbodyComponent* rb;
	//Puntero a la animacion
	AnimationComponent* animComp;

	btTransform transform;

	btQuaternion lastRotation;
	

	bool resetCamPosition;
	
	PlayerComponent* player;

	MouseComponent * mouseComponent;
};

#endif /* MOVECOMPONENT_H_ */
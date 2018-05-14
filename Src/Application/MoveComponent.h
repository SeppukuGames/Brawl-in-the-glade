#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "DynamicRigidbodyComponent.h"

class MoveComponent : public KeyInputComponent {
public:

	MoveComponent();
	virtual ~MoveComponent();

	virtual void start();
	virtual void tick(double elapsed);

	virtual bool keyPressed(const OIS::KeyEvent &arg);

	virtual bool keyReleased(const OIS::KeyEvent &arg);

	
private:
	//Ogre::Vector3 direction; 
	float velocity;
	btVector3 direction, oldDirection;
	DynamicRigidbodyComponent* rb;
	//Puntero a la animacion
	AnimationComponent* animComp;

};

#endif /* MOVECOMPONENT_H_ */
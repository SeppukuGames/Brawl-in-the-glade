#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "Component.h"
#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include <iostream>

class MoveComponent : public KeyInputComponent {
//---------------------------ATRIBUTOS-------------------------
private:
	Ogre::Vector3 direction;
	float velocity;

	//Puntero a la animacion
	AnimationComponent* animComp;
//---------------------------ATRIBUTOS-------------------------

//---------------------------MÉTODOS-------------------------
public:

	MoveComponent();

	virtual ~MoveComponent();

	virtual void start();

	virtual void tick(double elapsed);

	virtual void onCollision(GameObject *collision);

	virtual bool keyPressed(const OIS::KeyEvent &arg);

	virtual bool keyReleased(const OIS::KeyEvent &arg);


//---------------------------MÉTODOS-------------------------

};

#endif /* MOVECOMPONENT_H_ */
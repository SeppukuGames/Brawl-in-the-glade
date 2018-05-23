#ifndef BALACOMPONENT_H_
#define BALACOMPONENT_H_

#include "DynamicRigidbodyComponent.h"
#include <iostream>
#include "Physics.h"

class BalaComponent : public Component {

private:
	int vida; //Duracion de la bala en el aire.
	int velocidad;

	//FISICA
	btVector3 Direccion;
	btQuaternion rotacion;

	DynamicRigidbodyComponent *rb;
	btTransform transform;


public:

	//Constructora
	BalaComponent(const btVector3 & Dir) : Component()
	{
	
		Direccion = Dir;
	};

	virtual void start();
	virtual void tick(double elapsed);
	virtual void onCollision(GameObject *collision);

	//Destruye esta bala
	void DestruyeBala();
};
#endif
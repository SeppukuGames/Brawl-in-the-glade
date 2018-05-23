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

	virtual void start(){

		vida = 1000;
		velocidad = 20;

		//Mete el impulso inicial
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
		////Las colisiones hulio
		//std::cout << rb->getRigidbody()->getActivationState() << std::endl;

		//transform = rb->getRigidbody()->getWorldTransform();
		//
		////Aplicas la fuerza
		//transform.setRotation(rotacion);
		//rb->getRigidbody()->setLinearVelocity(Direccion *  velocidad);
		if (Direccion.length() < 5) {
			velocidad *= 10;
		}
		std::cout << "Direccion X:" << Direccion.getX() << "Direccion Y:" << Direccion.getZ() << std::endl;
		rb->getRigidbody()->applyCentralImpulse(Direccion * velocidad);
		//
		//rb->getRigidbody()->getMotionState()->setWorldTransform(transform);

	}
	//Suma la posicion, y luego en caso de chocarse con algo mandará un mensaje
	virtual void tick(double elapsed){
		
		if (vida > 0){
			

			vida--;
		}
	
		//Si vida = 0, se para.
		
	}

	
};
#endif
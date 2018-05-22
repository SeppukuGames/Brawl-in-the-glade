#ifndef _h_BalaComponent_h_
#define _h_BalaComponent_h_

#include "Component.h"
#include "DynamicRigidbodyComponent.h"
#include <iostream>

//COSAS DE UN HIPOTETICO PHYSICS MANAGER
/*#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsStaticPlaneShape.h>
#include <OgreBulletCollisionsBoxShape.h>

*/
class BalaComponent : public DynamicRigidbodyComponent {

public:

	//Constructora
	BalaComponent(btVector3 pos, btQuaternion q) : DynamicRigidbodyComponent()
	{
		rotacion = q;
		posicion = pos;
	};

	virtual void start(){
		transform = rb->getRigidbody()->getWorldTransform();
		vida = 1000;
		velocidad = 2;
	}
	//Suma la posicion, y luego en caso de chocarse con algo mandará un mensaje
	virtual void tick(double elapsed){
		
		if (vida > 0){
			
			rb->getRigidbody()->setLinearVelocity(posicion *  velocidad);


			rb->getRigidbody()->setCenterOfMassTransform(transform);
			rb->getRigidbody()->getMotionState()->setWorldTransform(transform);

			vida--;
		}
	
		//Si vida = 0, se para.
		
	}

	
	
private:
	int vida; //Duracion de la bala en el aire.
	int velocidad;

	btVector3 posicion;
	btQuaternion rotacion;

	DynamicRigidbodyComponent* rb;
	
	Ogre::SceneManager* _sceneMgr;
	btTransform transform;

};
#endif
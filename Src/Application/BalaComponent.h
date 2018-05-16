#ifndef _h_BalaComponent_h_
#define _h_BalaComponent_h_

#include "Component.h"
#include <iostream>

//COSAS DE UN HIPOTETICO PHYSICS MANAGER
/*#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsStaticPlaneShape.h>
#include <OgreBulletCollisionsBoxShape.h>

*/
class BalaComponent : public Component{

public:

	virtual void start(){
		posicion = _gameObject->getNode()->getPosition();
		direccion = _gameObject->getNode()->getOrientation();

		vida = 1000;
	}
	//Suma la posicion, y luego en caso de chocarse con algo mandará un mensaje
	virtual void tick(double elapsed){
		
		if (vida > 0){
			std::cout << vida << std::endl;
			posicion += direccion * Ogre::Vector3(0, 0, 1);
			_gameObject->getNode()->translate(posicion);
			vida--;
		}
	
		//Si vida = 0, se para.
		
	}

	int vida; //Duracion de la bala en el aire.
	int daño; //Daño que inflinge
	
private:

	Ogre::Vector3 posicion;
	
	Ogre::SceneManager* _sceneMgr;
	Ogre::Quaternion direccion;

};
#endif
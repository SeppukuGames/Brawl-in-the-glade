#ifndef _h_Bala_h_
#define _h_Bala_h_

#include "GameObject.h"
#include "EntityComponent.h"
#include "BalaComponent.h"
#include <iostream>
//COSAS DE UN HIPOTETICO PHYSICS MANAGER
/*#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsStaticPlaneShape.h>
#include <OgreBulletCollisionsBoxShape.h>

*/
class Bala : public GameObject{

public:
	//La posicion de la bala es local
	Bala(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 posisao, Ogre::Quaternion dir) : GameObject(mSceneMgr){
		std::cout << "Pium" << std::endl;
		posicion = posisao;
		direccion = dir;
		_sceneMgr = mSceneMgr;
		

		//Creamos un entity
		this->addComponent(new EntityComponent("ball.mesh"));		//Tenemos una bola con componente entidad.
		this->addComponent(new BalaComponent());
		this->getNode()->setScale(0.2, 0.2, 0.2);
	}

	void disparaBala(){

		

		//Fisica
		//OgreBulletCollisions::CollisionShape *bodyShape = new OgreBulletCollisions::SphereCollisionShape(0.2);
		//OgreBulletDynamics::RigidBody *rigidBody =
		//	new OgreBulletDynamics::RigidBody("rigidBody" + StringConverter::toString(_numEntities), _world);
		//
		//// Restitucion, friccion y masa
		//rigidBody->setShape(node, bodyShape, 0.6, 0.6, 5.0, position, Quaternion::IDENTITY);
		//rigidBody->setLinearVelocity(_camera->getDerivedDirection().normalisedCopy() * 20.0);
	}

private:

	GameObject* _camera;	//Cámara
	Ogre::Vector3 posicion;
	Ogre::SceneManager* _sceneMgr;
	Ogre::Quaternion direccion;

};
#endif
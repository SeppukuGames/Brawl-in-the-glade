#ifndef _h_Bala_h_
#define _h_Bala_h_

#include "GameObject.h"
#include "EntityComponent.h"
#include "BalaComponent.h"
#include "DynamicRigidbodyComponent.h"

class Bala : public GameObject{

public:
	//La posicion de la bala es local
	Bala(Ogre::SceneManager* mSceneMgr, btVector3 pos, btQuaternion dir); 

	void iniciaFisica();

private:

	GameObject* _camera;	//Cámara
	btVector3 posicion;
	
	Ogre::SceneManager* _sceneMgr;
	btQuaternion direccion;

	//Atributos fisicos
	//btVector3 posFisica;
	//btTransform transFisica;
	//btDefaultMotionState balaMotionState;

	btCollisionShape * shapeBala;
	btTransform balaTransform;

	btDefaultMotionState * balaMotionState;
	//Colision shape
	btCollisionShape * balaShape;

	btScalar balaMass;
	btVector3 balaInercia;
};
#endif
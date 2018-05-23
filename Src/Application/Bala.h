#ifndef _h_Bala_h_
#define _h_Bala_h_

#include "GameObject.h"
#include "DynamicRigidbodyComponent.h"

class Bala : public GameObject{

public:

	Bala(Ogre::SceneManager* mSceneMgr, const btVector3 & pos, const btQuaternion & dir); 

	void iniciaFisica();

private:
	Ogre::SceneManager* _sceneMgr;

	btVector3 posicion;	
	btQuaternion direccion;

	//FISICA
	btTransform balaTransform;					//Transform

	btDefaultMotionState * balaMotionState;

	//Colision shape
	btCollisionShape * balaShape;

	btScalar balaMass;
	btVector3 balaInercia;
};
#endif
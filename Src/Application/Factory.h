#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"
#include "Bala.h"
#include "DynamicRigidbodyComponent.h"

//Factoría para la creación de enemigos
static class ObjFactory{
public:

	EnemyPrototype* typeEnemy;

	//Se crea el enemigo
	void initialize(Ogre::SceneManager * mSceneMgr){
		typeEnemy = new EnemyType1(mSceneMgr);
	}

	EnemyPrototype * getTypeEnemy(){ return typeEnemy->clone(); };
};

class MainGame;
class BulletFactory{

public:

	//No debería ser static porque entonces pa qué quieres una clase jaja
	//Pero de momento se queda así.
	static void creaBala(Ogre::SceneManager* mSceneManager, const btVector3 & pos, const btQuaternion & dir){

		//Ogre::Quaternion testDir = Ogre::Quaternion(0, 0, 1,0); //180º
		Bala* nuevaBala = new Bala(mSceneManager, pos, dir);
	}



};

#endif /* FACTORY_H_ */
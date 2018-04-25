#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"
#include "Bala.h"

//Factoría para la creación de enemigos
class ObjFactory{

public:

	static EnemyPrototype* typeEnemy;

	//Se crea el enemigo
	static void initialize(Ogre::SceneManager * mSceneMgr){
		typeEnemy = new EnemyType1(mSceneMgr);
	}

	static EnemyPrototype * getTypeEnemy(){ return typeEnemy->clone(); };

};

class TutorialApplication;
class BulletFactory{

	public:

	//No debería ser static porque entonces pa qué quieres una clase jaja
	//Pero de momento se queda así.
		static void creaBala(Ogre::SceneManager* mSceneManager, Ogre::Quaternion dir, Ogre::Vector3 pos){

	        Bala* nuevaBala = new Bala(mSceneManager, pos, dir);
	}

		

};

#endif /* FACTORY_H_ */

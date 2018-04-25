#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"
#include "Bala.h"

//Factor�a para la creaci�n de enemigos
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

	//No deber�a ser static porque entonces pa qu� quieres una clase jaja
	//Pero de momento se queda as�.
		static void creaBala(Ogre::SceneManager* mSceneManager, Ogre::Quaternion dir, Ogre::Vector3 pos){

	        Bala* nuevaBala = new Bala(mSceneManager, pos, dir);
	}

		

};

#endif /* FACTORY_H_ */

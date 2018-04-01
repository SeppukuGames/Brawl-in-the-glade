#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"

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

#endif /* FACTORY_H_ */

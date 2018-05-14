#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"

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

#endif /* FACTORY_H_ */

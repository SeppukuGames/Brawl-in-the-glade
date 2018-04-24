#ifndef ENEMYTYPE1_H_
#define ENEMYTYPE1_H_


#include "EnemyPrototype.h"

//Clase que define un tipo concreto de enemigo
class EnemyType1 : public EnemyPrototype
{

public:

	EnemyType1(Ogre::SceneManager * mSceneMgr);
	EnemyPrototype * clone();




};

#endif /* ENEMYTYPE1_H_*/
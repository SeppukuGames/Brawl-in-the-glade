#ifndef ENEMYPROTOTYPE_H_
#define ENEMYPROTOTYPE_H_

#include "GameObject.h"

//Clase virtual para declarar el prototipo del enemigo
class EnemyPrototype : public GameObject{

public:

	virtual EnemyPrototype * clone() = 0;
	EnemyPrototype(Ogre::SceneManager *mScn) :GameObject(mScn){};

};

#endif /* ENEMYPROTOTYPE_H_*/

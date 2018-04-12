#ifndef ENEMYPROTOTYPE_H_
#define ENEMYPROTOTYPE_H_

#include "GameComponent.h"

//Clase virtual para declarar el prototipo del enemigo
class EnemyPrototype : public GameComponent{

public:

	virtual EnemyPrototype * clone() = 0;
	EnemyPrototype(Ogre::SceneManager *mScn) :GameComponent(mScn){};

};

#endif /* ENEMYPROTOTYPE_H_*/

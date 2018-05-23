#ifndef FACTORY_H_
#define FACTORY_H_

#include "EnemyType1.h"
#include "Bala.h"
#include "DynamicRigidbodyComponent.h"

//Factor�a para la creaci�n de enemigos
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

	//No deber�a ser static porque entonces pa qu� quieres una clase jaja
	//Pero de momento se queda as�.
	static void creaBala(Ogre::SceneManager* mSceneManager, const btVector3 & pos, const btVector3  & dir, std::string id){

		Bala* nuevaBala = new Bala(mSceneManager, pos, dir, id);
	}



};

#endif /* FACTORY_H_ */
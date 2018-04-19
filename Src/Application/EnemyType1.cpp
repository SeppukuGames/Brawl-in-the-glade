#include "EnemyType1.h"
#include "EntityComponent.h"
#include "AnimationComponent.h"
#include "MoveComponent.h" 

EnemyType1::EnemyType1(Ogre::SceneManager * mSceneMgr) : EnemyPrototype(mSceneMgr)
{
}

EnemyPrototype * EnemyType1::clone(){

	EnemyType1 * enemy = new EnemyType1(node->getCreator());
	enemy->getNode()->setScale(Ogre::Vector3(1, 1, 1));

	//Se a�aden los componentes
	//Hemos metido el ninja aqu� por probar. Es importante que el elemento que tenga un Move Component tenga tambien el Animation porque sino se rompe. 
	//(Idealmente, solo el jugador va a tener el moveComponent asi que no deber�a haber problema, �no?)
	enemy->addComponent(new EntityComponent("ninja.mesh")); //Se a�ade la entidad
	enemy->addComponent(new AnimationComponent("Idle1"));//Se a�ade un componente
	enemy->addComponent(new MoveComponent());//Se a�ade un componente

	return enemy;
}


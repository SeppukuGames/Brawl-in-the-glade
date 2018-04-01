#include "EnemyType1.h"
#include "EntityComponent.h"
//#include "MoveComponent.h" //Queda arreglar el MoveComponent

EnemyType1::EnemyType1(Ogre::SceneManager * mSceneMgr) : EnemyPrototype(mSceneMgr)
{
}

EnemyPrototype * EnemyType1::clone(){

	EnemyType1 * enemy = new EnemyType1(node->getCreator());
	enemy->getNode()->setScale(Ogre::Vector3(0.5, 0.5, 0.55));

	//Se añaden los componentes
	enemy->addComponent(new EntityComponent("ogrehead.mesh")); //Se añade la entidad
	//enemy->addComponent(new MoveComponent());//Se añade un componente

	return enemy;
}


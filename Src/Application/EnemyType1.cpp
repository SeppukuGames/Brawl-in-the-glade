#include "EnemyType1.h"
#include "EntityComponent.h"
//#include "MoveComponent.h" //Queda arreglar el MoveComponent

EnemyType1::EnemyType1(Ogre::SceneManager * mSceneMgr) : EnemyPrototype(mSceneMgr)
{
}

EnemyPrototype * EnemyType1::clone(){

	EnemyType1 * enemy = new EnemyType1(node->getCreator());
	enemy->getNode()->setScale(Ogre::Vector3(0.5, 0.5, 0.55));

	//Se a�aden los componentes
	enemy->addComponent(new EntityComponent("ogrehead.mesh")); //Se a�ade la entidad
	//enemy->addComponent(new MoveComponent());//Se a�ade un componente

	return enemy;
}


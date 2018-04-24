#include "EnemyType1.h"
#include "EntityComponent.h"
#include "AnimationComponent.h"
#include "MoveComponent.h" 
#include "DynamicRigidbodyComponent.h"
#include "EnemyComponent.h"

EnemyType1::EnemyType1(Ogre::SceneManager * mSceneMgr) : EnemyPrototype(mSceneMgr)
{
	
	node->setScale(Ogre::Vector3(Ogre::Real(0.10), Ogre::Real(0.1), Ogre::Real(0.15)));

	//Se añaden los componentes
	//Hemos metido el ninja aquí por probar. Es importante que el elemento que tenga un Move Component tenga tambien el Animation porque sino se rompe. 
	//(Idealmente, solo el jugador va a tener el moveComponent asi que no debería haber problema, ¿no?)
	addComponent(new EntityComponent("ninja.mesh")); //Se añade la entidad

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 initialPosition(20, 100, 0);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(initialPosition);

	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *fallMotionState = new btDefaultMotionState(startTransform);

	//Colision shape
	//Creamos la esfera de radio 1
	btCollisionShape* fallShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));
	//btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass(70.0f);
	btVector3 fallInertia(0, 0, 0);

	DynamicRigidbodyComponent* rbComponent = new DynamicRigidbodyComponent(fallMotionState, fallShape, mass, fallInertia);

	addComponent(rbComponent);//Se añade un componente

	rbComponent->getRigidbody()->setRestitution(1);

	addComponent(new EnemyComponent());


}

EnemyPrototype * EnemyType1::clone(){
	return (new EnemyType1(*this));
	
}


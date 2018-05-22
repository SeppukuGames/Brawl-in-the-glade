#include "Bala.h"
#include "MainGame.h"

Bala::Bala(Ogre::SceneManager* mSceneMgr, btVector3 pos, btQuaternion dir) : GameObject(mSceneMgr) {

	posicion = pos;
	direccion = dir;

	_sceneMgr = mSceneMgr;


	//Creamos un entity

	this->addComponent(new EntityComponent("ogrehead.mesh"));		//Tenemos una bola con componente entidad.
	this->addComponent(new BalaComponent(pos, dir));
	//this->getNode()->setScale(0.2, 0.2, 0.2);
	//this->getNode()->translate(posicion);		//En principio no hace falta?	//Situamos la bala en la posicion que queremos (la del objeto que la dispara).

	MainGame::getInstance()->añadeGameObject(this);

}



void Bala::iniciaFisica(){


	//TODO: Meterle física. Una velocidad lineal o algo así.
	//Fisica
	//OgreBulletCollisions::CollisionShape *bodyShape = new OgreBulletCollisions::SphereCollisionShape(0.2);
	//OgreBulletDynamics::RigidBody *rigidBody =
	//	new OgreBulletDynamics::RigidBody("rigidBody" + StringConverter::toString(_numEntities), _world);
	//
	//// Restitucion, friccion y masa
	//rigidBody->setShape(node, bodyShape, 0.6, 0.6, 5.0, position, Quaternion::IDENTITY);
	//rigidBody->setLinearVelocity(_camera->getDerivedDirection().normalisedCopy() * 20.0);

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 balaInitialPosition(posicion.x, posicion.y, posicion.z);	//La posición del jugador
	balaTransform.setIdentity();
	balaTransform.setOrigin(balaInitialPosition);


	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	balaMotionState = new btDefaultMotionState(balaTransform);

	//Colision shape
	balaShape = new btBoxShape(btVector3(2.0f, 2.0f, 2.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	balaMass = 10.0f;
	balaInercia = btVector3(0, 0, 0);
}
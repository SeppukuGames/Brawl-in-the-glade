#include "Bala.h"
#include "EntityComponent.h"
#include "BalaComponent.h"
#include "MainGame.h"

#include <string>

Bala::Bala(Ogre::SceneManager* mSceneMgr, const btVector3 & pos, const btVector3  & dir, std::string idBala) : GameObject(mSceneMgr, "Bala" + idBala) {

	posicion = pos;
	direccion = dir;

	_sceneMgr = mSceneMgr;

	
	std::cout << "Bala" + idBala << std::endl;

	//iniciaFisica();
	//Motion state
	btVector3 BalaInitialPosition(posicion);

	
	balaTransform.setIdentity();
	balaTransform.setOrigin(BalaInitialPosition);


	//actually contruvc the body and add it to the dynamics world
	balaMotionState = new btDefaultMotionState(balaTransform);

	//Colision shape
	balaShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));	//DEBERIA SER OTRO ROLLO


	//set the mass of the object. a mass of "0" means that it is an immovable object
	balaMass = 1.0f;
	balaInercia = btVector3(0, 0, 0);

	this->addComponent(new EntityComponent("knot.mesh"));		//Tenemos una bola con componente entidad.
	getNode()->setScale(0.2, 0.2, 0.2);
	this->addComponent(new DynamicRigidbodyComponent(balaMotionState, balaShape, balaMass, balaInercia));
	this->addComponent(new BalaComponent(direccion));
	
	//this->getNode()->setScale(0.2, 0.2, 0.2);
	//this->getNode()->translate(posicion);		//En principio no hace falta?	//Situamos la bala en la posicion que queremos (la del objeto que la dispara).

	MainGame::getInstance()->añadeGameObject(this);

}


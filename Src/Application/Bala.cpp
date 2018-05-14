#include "Bala.h"
#include "TutorialApplication.h"

Bala::Bala(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos, Ogre::Quaternion dir) : GameObject(mSceneMgr) {

posicion = pos;
direccion = dir;
_sceneMgr = mSceneMgr;


//Creamos un entity

this->addComponent(new EntityComponent("ogrehead.mesh"));		//Tenemos una bola con componente entidad.
this->addComponent(new BalaComponent());
//this->getNode()->setScale(0.2, 0.2, 0.2);
this->getNode()->translate(posicion);			//Situamos la bala en la posicion que queremos (la del objeto que la dispara).

//TutorialApplication::getInstance()->añadeGameObject(this);			//Añadimos la bala a los actores.
TutorialApplication::getInstance()->añadeGameObject(this);

}

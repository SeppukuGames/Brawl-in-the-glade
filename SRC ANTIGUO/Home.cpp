
#include "Home.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameObject.h"
#include "EntityComponent.h"
#include "MenuPrincipal.h"

#include <stdio.h>

#include <time.h>
#include <iostream>


using namespace Ogre;

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

//-------------------------------------------------------------------------------------
Home::Home(void)
{
	partidaTerminada = false;
	playIndex = 0;
}
//-------------------------------------------------------------------------------------

//Borrar luz, cámara,
//MainGame::~MainGame(void)
//{
//	
//}

//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------

void Home::createLights(void)
{
	//Creamos luz ambiental
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Creamos una luz
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);

	//Damos posición al nodo de la luz
	lightNode->setPosition(20, 80, 50);
}

//-------------------------------------------------------------------------------------

void Home::createCameras(void)
{
	//La inicializamos
	mCamera->setPosition(Ogre::Vector3(0, 200, 100));
	mCamera->lookAt(Ogre::Vector3(0, -80, -300));
	mCamera->setNearClipDistance(5);

	//Creamos camara
	cam = new GameObject(mSceneMgr);
	camNode = cam->getNode();
	camNode->attachObject(mCamera);
	camNode->setPosition(0, 47, 222);
	actors_.push_back(cam);

}

//-------------------------------------------------------------------------------------

void Home::createEntities(void)
{

	//----------------------MENUs------------------------	
	menuPrincipal = new GameObject(mSceneMgr);
	menuPrincipal->addComponent(new MenuPrincipal());
	dynamic_cast<MenuPrincipal*> (menuPrincipal->getComponent(ComponentName::MENUPRINCIPAL))->SetMainGameRef(this);

	actors_.push_back(menuPrincipal);

	//----------------------MENUs------------------------
}

void Home::createGUI() {


}

//-------------------------------------------------------------------------------------
void Home::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();

	createGUI();

}
void Home::initGame() {
	mShutDown = true;
	playIndex = 1;
	instance = NULL;
}
void Home::quitGame() {
	playIndex = -1;
	mShutDown = true;
}

Home *Home::instance = 0;

Home *Home::getInstance()
{
	if (!instance)
		instance = new Home;
	return instance;

}



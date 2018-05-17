#include "EscenaMenu.h"

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#include "Boton.h"

using namespace Ogre;

EscenaMenu::EscenaMenu(void){}

void EscenaMenu::createLights(void)
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

void EscenaMenu::createCameras(void)
{
	//Creamos camara
	cam = new GameObject(mSceneMgr);
	camNode = cam->getNode();
	camNode->attachObject(mCamera);
	camNode->setPosition(0, 47, 222);	
	actors_.push_back(cam);

	/*
	SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	// create the camera
	Camera* cam = mSceneMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 140);
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	*/
}

//-------------------------------------------------------------------------------------

void EscenaMenu::createEntities(void)
{
	//------------------------- OVERLAY ---------------------------------------

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	FontManager& fM = FontManager::getSingleton();

	//------FONDO---------
	Fondo =  static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "Fondo"));

	Fondo->setMetricsMode(Ogre::GMM_PIXELS);
	Fondo->setPosition(30, 0);
	Fondo->setDimensions(1000, 500);
	Fondo->setMaterialName("panel"); // Optional background material 
	
	// Create an overlay, and add the panel*/
	overlay = overlayManager.create("OverlayName");	
	overlay->add2D(Fondo);

	// Show the overlay*/
	overlay->show();

	boton = new GameObject(mSceneMgr);
	boton->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
	boton->addComponent(new Boton());

	actors_.push_back(boton);
}

//-------------------------------------------------------------------------------------
void EscenaMenu::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();

}

EscenaMenu *EscenaMenu::instance = 0;

EscenaMenu *EscenaMenu::getInstance()
{
	if (!instance)
		instance = new EscenaMenu;
	return instance;

}


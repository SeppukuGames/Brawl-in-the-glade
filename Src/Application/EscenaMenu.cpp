#include "EscenaMenu.h"

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

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

	// Create a panel
	for (int i = 1; i <= 3; i++){

		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "panel" + std::to_string(i)));

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(450, 450+(50*i));
		panel->setDimensions(0, 0);
		panel->setMaterialName("panel"); // Optional background material 

		//texto		
		TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaName" + std::to_string(i)));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 50);
		textArea->setDimensions(100, 100);
		switch (i)
		{
		case 1:
			textArea->setCaption("Comenzar partida");
			break;
		case 2:
			textArea->setCaption("Controles");
			break;
		case 3:
			textArea->setCaption("Salir");
			break;
		default:
			break;
		}
		
		textArea->setCharHeight(50);
		textArea->setFontName("Trebuchet");	
		textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));
		textArea->setColourTop(ColourValue(1.0, 1.0, 1.0));

		// Add the text area to the panel		
		panel->addChild(textArea);

		botones.push_back(panel);
	}	

	// Create an overlay, and add the panel*/
	overlay = overlayManager.create("OverlayName");
	for (int i = 0; i < botones.size(); i++){
		overlay->add2D(botones[i]);			
	}
	overlay->add2D(Fondo);

	// Show the overlay*/
	overlay->show();	

	Refrescar(1, "Controles");

}

void EscenaMenu::Refrescar(int boton, std::string textoBoton)
{
	OverlayManager& overlayManager = OverlayManager::getSingleton();
	FontManager& fM = FontManager::getSingleton();

	delete botones[boton];
	overlay = nullptr;

	OverlayContainer* panel = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "panel" + std::to_string(cont)));

	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(450, 450 + (50*(boton+1)));
	panel->setDimensions(0, 0);
	panel->setMaterialName("panel"); // Optional background material 

	//texto		
	TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea", "TextAreaName"));
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
	textArea->setPosition(70, 50);
	textArea->setDimensions(100, 100);
	textArea->setCaption(textoBoton);

	textArea->setCharHeight(50);
	textArea->setFontName("Trebuchet");
	textArea->setColourBottom(ColourValue(0.0, 0.0, 1.0));
	textArea->setColourTop(ColourValue(0.0, 1.0, 1.0));

	// Add the text area to the panel		
	panel->addChild(textArea);
	botones[boton] = panel;

	// Refrescar overlay*/
	overlay = overlayManager.create("OverlayName" + std::to_string(cont));
	for (int i = 0; i < botones.size(); i++){
		overlay->add2D(botones[i]);
	}
	overlay->add2D(Fondo);

	// Show the overlay*/
	overlay->show();
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


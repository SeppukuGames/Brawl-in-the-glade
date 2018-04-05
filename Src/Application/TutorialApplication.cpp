/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------
This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameComponent.h"
#include "EntityComponent.h"
#include "MoveComponent.h"
#include <OgreException.h>


#include <time.h>
using namespace Ogre;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------

/*TutorialApplication::~TutorialApplication(void)
{
}
*/
//-------------------------------------------------------------------------------------

void TutorialApplication::createLights(void)
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

void TutorialApplication::createCameras(void)
{
	//Creamos camara
	//LA CÁMARA YA VIENE CREADA POR BASE APPLICATION, SOLO CREAMOS EL NODO
	SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->attachObject(mCamera);
	camNode->setPosition(0, 47, 222);

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

void TutorialApplication::createEntities(void)
{
	//Creamos entidades. DEBERIAMOS DAR NOMBRES A ENTIDADES Y NODOS
	/*
	GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);

	//Componentes que se añaden al Game Component
	OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5,5,5)));
	OgritoQueRota->addComponent(new Transform(Ogre::Vector3(1, 0, 0)));
	OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	actors_.push_back(OgritoQueRota);
	*/

	
	srand(time(NULL));
	int random = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			random = rand() % 101;
			GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);
			OgritoQueRota->getNode()->setPosition(Ogre::Vector3((i * 50) - 300, -20, (j * 50) - 300));
			OgritoQueRota->getNode()->setScale(Ogre::Vector3(5, 5, 5));

			if (random % 7 == 0)
				OgritoQueRota->addComponent(new EntityComponent("arbol.mesh"));
			else
				OgritoQueRota->addComponent(new EntityComponent("suelo.mesh"));
			actors_.push_back(OgritoQueRota);
		}
	}

	ObjFactory::initialize(mSceneMgr);

	EnemyPrototype * ogro;//Prototipo del enemigo

	for (int i = 0; i < 50; i++){
		ogro = ObjFactory::getTypeEnemy();
		ogro->getNode()->setPosition(Ogre::Vector3((i * 20), 0, (i * 20)));
		actors_.push_back(ogro); 
	}
	 //------------------------- OVERLAY ---------------------------------------
	


	OverlayManager& overlayManager = OverlayManager::getSingleton();
	FontManager& fM = FontManager::getSingleton();

	
	// Create a panel
	OverlayContainer* panel = static_cast<OverlayContainer*>(
	overlayManager.createOverlayElement("Panel", "PanelName"));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(100, 100);
	panel->setDimensions(100, 100);
	panel->setMaterialName("BaseWhite"); // Optional background material

	/*
	// Create a text area
	TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
	overlayManager.createOverlayElement("TextArea", "TextAreaName"));
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(0, 0);
	textArea->setDimensions(100, 100);
	textArea->setCaption("Hello, World!");
	textArea->setCharHeight(16);
	textArea->setFontName("Trebuchet MS");
	textArea->setColourBottom(ColourValue(0.3, 0.5, 0.3));
	textArea->setColourTop(ColourValue(0.5, 0.7, 0.5));
	*/
	// Create an overlay, and add the panel
	Overlay* overlay = overlayManager.create("OverlayName");
	overlay->add2D(panel);

	// Add the text area to the panel
	// panel->addChild(textArea);
	

	// Show the overlay
	overlay->show();
	
	











	//panel->setMaterialName("MaterialName"); // Optional background material

	/*
	GameComponent * ogro= new GameComponent(mSceneMgr);
	ogro->getNode()->setScale(Ogre::Vector3(0.5, 0.5, 0.55));

	ogro->addComponent(new EntityComponent("ogrehead.mesh"));
	ogro->addComponent(new MoveComponent());
	actors_.push_back(ogro);*/

	//Metodos utiles de la escena:
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();
}

TutorialApplication *TutorialApplication::instance = 0;


TutorialApplication *TutorialApplication::getInstance()
{
	if (!instance)
		instance = new TutorialApplication;
	return instance;
}

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

//#include "GameComponent.h"
#include "GameObject.h"
#include "EntityComponent.h"
#include "MoveComponent.h"
#include "MoveCameraComponent.h"
#include "SoundEngine/irrKlang.h"
#include <stdio.h>
#include "AnimationComponent.h"

#include "CollisionComponent.h"    //Incluido en el merge de animationComponent

#include <time.h>
#include <iostream>
#include "Enemigo.h"

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irrklang;
using namespace Ogre;

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

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

void TutorialApplication::createSoundEngine(void) 
{
	// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
	}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped

	engine->play2D("../../Media/Sounds/getout.ogg", true);


	// play a single sound
	engine->play2D("../../Media/Sounds/bell.wav");

	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	//engine->drop(); // delete engine

}


//-------------------------------------------------------------------------------------

void TutorialApplication::createLights(void)
{
	//Creamos luz ambiental
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Creamos una luz
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);

	//Damos posici�n al nodo de la luz
	lightNode->setPosition(20, 80, 50);
}

//-------------------------------------------------------------------------------------

void TutorialApplication::createCameras(void)
{
	//Creamos camara
	//LA C�MARA YA VIENE CREADA POR BASE APPLICATION, SOLO CREAMOS EL NODO
	//SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//camNode->attachObject(mCamera);
	//camNode->setPosition(0, 47, 222);

	GameObject * cam = new GameObject(mSceneMgr);
	SceneNode* camNode = cam->getNode()->createChildSceneNode();
	camNode->attachObject(mCamera);
	camNode->setPosition(0, 47, 222);
	cam->addComponent(new MoveCameraComponent(BaseApplication::mWindow, mSceneMgr));
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

void TutorialApplication::createEntities(void)
{
	//Creamos entidades. DEBERIAMOS DAR NOMBRES A ENTIDADES Y NODOS
	/*
	GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);

	//Componentes que se a�aden al Game Component
	OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5,5,5)));
	OgritoQueRota->addComponent(new Transform(Ogre::Vector3(1, 0, 0)));
	OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	actors_.push_back(OgritoQueRota);
	*/

	
	srand((unsigned int)time(NULL));

	
	int random = 0;
	for (int i = 0; i < 40; i++){
		for (int j = 0; j < 40; j++){
			random = rand() % 101;
			//Game Component ahora es Game Object
			GameObject * OgritoQueRota = new GameObject(mSceneMgr);

			OgritoQueRota->getNode()->setPosition(Ogre::Vector3((i * 50) - 300, -20, (j * 50) - 300));
			OgritoQueRota->getNode()->setScale(Ogre::Vector3(5, 5, 5));

			if (j == 20 && i == 20){

				OgritoQueRota->addComponent(new EntityComponent("Torre.mesh"));
				std::cout << "POsicion de la torre: " << OgritoQueRota->getNode()->getPosition().x << ", " <<
					OgritoQueRota->getNode()->getPosition().y << ", " << OgritoQueRota->getNode()->getPosition().z << "\n";
			}
			else{
				if (random % 6 == 0)
					OgritoQueRota->addComponent(new EntityComponent("arbol.mesh"));
				else
					OgritoQueRota->addComponent(new EntityComponent("suelo.mesh"));
			}

			actors_.push_back(OgritoQueRota);
		}
	}


	ObjFactory::initialize(mSceneMgr);

	EnemyPrototype * ogro;//Prototipo del enemigo
	//Super �til
	for (int i = 0; i < 1; i++){
		ogro = ObjFactory::getTypeEnemy();
		ogro->getNode()->setPosition(Ogre::Vector3((i * 20), 0, (i * 20)));
		actors_.push_back(ogro); 
	}

	/*
	GameComponent * ogro= new GameComponent(mSceneMgr);
=======
	GameComponent * ogro = new GameComponent(mSceneMgr);
>>>>>>> origin/CamaraBasica
	ogro->getNode()->setScale(Ogre::Vector3(0.5, 0.5, 0.55));

	//ogro->getNode()->addChild(camNode);	//Esto es para asociar la c�mara a sinbad (no hace falta ahora)
	
	ogro->addComponent(new EntityComponent("ogrehead.mesh"));
	ogro->addComponent(new MoveComponent());
<<<<<<< HEAD
	actors_.push_back(ogro);*/

	//actors_.push_back(ogro);

	//20 a 4
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			//GameComponent a GameObject
			GameObject * enemigo = new GameObject(mSceneMgr);
			enemigo->getNode()->setScale(0.5, 0.5, 0.5);
			enemigo->getNode()->setPosition(Ogre::Vector3((rand() % 40 * 50) - 300, 0, (rand() % 40 * 50) - 300));

			enemigo->addComponent(new EntityComponent("ogrehead.mesh")); //Ninja.mesh
			enemigo->addComponent(new Enemigo());
			enemigo->addComponent(new CollisionComponent());		//Da un lag de la hostia cuando los enemigos colisionan contra el suelo.
			//enemigo->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
			//enemigo->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent
			actors_.push_back(enemigo);
		}
	}

	
	/*
	GameObject* ninja = new GameObject(mSceneMgr);

	ninja->getNode()->setScale(0.5, 0.5, 0.5);
	ninja->getNode()->setPosition(Ogre::Vector3((rand() % 40 * 50) - 300, 0, (rand() % 40 * 50) - 300));

	ninja->addComponent(new EntityComponent("ninja.mesh")); //Ninja.mesh
	//ninja->addComponent(new Enemigo());
	ninja->addComponent(new CollisionComponent());		//Da un lag de la hostia cuando los enemigos colisionan contra el suelo.
	ninja->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
	ninja->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent
	actors_.push_back(ninja);
	*/

}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();

	createSoundEngine();
}

TutorialApplication *TutorialApplication::instance = 0;

//Hab�a conflicto aqui pero es igual lol
TutorialApplication *TutorialApplication::getInstance()
{
	if (!instance)
		instance = new TutorialApplication;
	return instance;

}


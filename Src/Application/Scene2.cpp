#include "Scene2.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>

#include "GraphicManager.h"
#include "EntityComponent.h"


using namespace Ogre;

Scene2::Scene2() : Scene()
{
}

void Scene2::CreateScene()
{
	CreateLights();

	CreateCameras();

	CreateEntities();
}

void Scene2::CreateLights(void)
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Creamos una luz
	Light* light = sceneMgr->createLight("MainLightScene2");
	SceneNode* lightNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);

	//Damos posición al nodo de la luz
	lightNode->setPosition(20, 80, 50);
}

void Scene2::CreateCameras(void) 
{
	//Creamos la cámara
	camera = sceneMgr->createCamera("CamScene2");
	//La inicializamos
	camera->setPosition(Ogre::Vector3(0, 200, 100));
	camera->lookAt(Ogre::Vector3(0, -80, -300));
	camera->setNearClipDistance(5);

	SceneNode* camNode = sceneMgr->createSceneNode("NodoCamaraScene2");
	camNode->attachObject(camera);
	camNode->setPosition(0, 47, 222);

	//TODO: Camara GameObject
	//Creamos camara
	//cam = new GameObject(mSceneMgr);
	
	//cam->addComponent(new MoveCameraComponent(BaseApplication::mWindow, mSceneMgr));

	//dynamic_cast<MoveCameraComponent*> (cam->getComponent(ComponentName::MOVE_CAMERA))->setMainGameRef(this);
	//actors_.push_back(cam);

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



void Scene2::CreateEntities(void)
{
	GameObject* ogrito = new GameObject(sceneMgr,"Ogrito");
	ogrito->AddComponent(new EntityComponent("ogrehead.mesh")); //Ninja.mesh

	actors.push_back(ogrito);
}


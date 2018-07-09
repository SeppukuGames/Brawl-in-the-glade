#include "Scene1.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>

#include "GraphicManager.h"
#include "EntityComponent.h"
#include "PrefabManager.h"

using namespace Ogre;

Scene1::Scene1() : Scene()
{
	CreateScene();
}

void Scene1::CreateScene()
{
	CreateLights();

	CreateCameras();

	CreateEntities();
}

void Scene1::CreateLights(void)
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Creamos una luz
	Light* light = sceneMgr->createLight("MainLightScene1");
	SceneNode* lightNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);

	//Damos posición al nodo de la luz
	lightNode->setPosition(20, 80, 50);
}

void Scene1::CreateCameras(void) 
{
	//Creamos la cámara
	camera = sceneMgr->createCamera("CamScene1");
	//La inicializamos
	camera->setPosition(Ogre::Vector3(0, 200, 100));
	camera->lookAt(Ogre::Vector3(0, -80, -300));
	camera->setNearClipDistance(5);

	SceneNode* camNode = sceneMgr->createSceneNode("NodoCamaraScene1");
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

void Scene1::CreateEntities(void)
{
	GameObject* ogrito = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJA);
	actors.push_back(ogrito);

	GameObject * gm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::GAMEMANAGER);
	actors.push_back(gm);
}


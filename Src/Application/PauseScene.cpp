#include "PauseScene.h"
#include "Scene.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <Box2D.h>

#include "GraphicManager.h"
#include "EntityComponent.h"
#include "PrefabManager.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerComponent.h"
#include "AudioManager.h"

using namespace Ogre;

PauseScene::PauseScene() : Scene()
{
}

void PauseScene::CreateScene()
{
	CreateCameras();
	CreateLights();
	CreateEntities();
}

bool PauseScene::Tick(double elapsed){

	if (!HandleInput())
		return false;

	Update(elapsed);

	if (!Render())
		return false;

	return true;
}

void PauseScene::CreateCameras(void)
{
	//Creamos la cámara
	camera = sceneMgr->createCamera("CamPauseScene");
	//La inicializamos
	camera->setPosition(Ogre::Vector3(0, 200, 100));
	camera->lookAt(Ogre::Vector3(0, -80, -300));
	camera->setNearClipDistance(5);

	SceneNode* camNode = sceneMgr->createSceneNode("NodoCamaraPauseScene");
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

void PauseScene::CreateLights(void)
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//Creamos una luz
	Light* light = sceneMgr->createLight("MainLightPauseScene");
	SceneNode* lightNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);

	//Damos posición al nodo de la luz
	lightNode->setPosition(20, 80, 50);
}
void PauseScene::CreateEntities(void)
{
	//TODO: Panel con botones
	//GameObject * player = new GameObject(sceneMgr, "playerPausa");
	//player->AddComponent(new EntityComponent("ogrehead.mesh"));
	//player->AddComponent(new BoxColliderComponent(50, 50));
	//player->AddComponent(new RigidbodyComponent());
	//player->AddComponent(new PlayerComponent());
	//actors.push_back(player);

	GameObject * pm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::PAUSEMANAGERPREFAB);
	actors.push_back(pm);

	GameObject * A = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	actors.push_back(A);
}
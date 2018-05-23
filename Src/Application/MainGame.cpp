/*
-----------------------------------------------------------------------------
Filename:    MainGame.cpp
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

#include "MainGame.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameObject.h"
#include "EntityComponent.h"
#include "MoveComponent.h"
#include "MouseComponent.h"
#include "MoveCameraComponent.h"
#include <stdio.h>
#include "AnimationComponent.h"
#include "PlayerComponent.h"
#include "TowerComponent.h"
#include <time.h>
#include <iostream>
#include "Enemigo.h"
#include "RigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "TestCollisionComponent1.h"
#include "TestCollisionComponent2.h"
#include "BalaComponent.h"
#include "MenuPausa.h"
#include "MenuGameOver.h"
#include "PanelOleada.h"

using namespace Ogre;

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

//-------------------------------------------------------------------------------------
MainGame::MainGame(void)
{
	partidaTerminada = false;
	playIndex = 1;
}
//-------------------------------------------------------------------------------------

//Borrar luz, cámara,
//MainGame::~MainGame(void)
//{
//	
//}

//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------

void MainGame::createLights(void)
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

void MainGame::createCameras(void)
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
	cam->addComponent(new MoveCameraComponent(BaseApplication::mWindow, mSceneMgr));

	dynamic_cast<MoveCameraComponent*> (cam->getComponent(ComponentName::MOVE_CAMERA))->setMainGameRef(this);
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

void MainGame::createEntities(void)
{


	//Todos los rigidbody necesitan una referencia al collision shape.
	//Collision shape es UNICAMENTE	para colisiones. No tiene masa, inercia,etc.
	//Si hay muchos rigidbodies con la misma colision, es bueno utilizar el mismo collision shape.


	//----------------------NINJA---------------------------------

	ninja = new GameObject(mSceneMgr);
	ninja->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
	ninja->addComponent(new EntityComponent("ninja.mesh")); //Ninja.mesh
	ninja->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
	ninja->addComponent(new PlayerComponent());
	dynamic_cast<PlayerComponent*> (ninja->getComponent(ComponentName::PLAYER))->setMainGameRef(this);

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 ninjaInitialPosition(600, 0, 700);

	btTransform ninjaTransform;
	ninjaTransform.setIdentity();
	ninjaTransform.setOrigin(ninjaInitialPosition);


	//actually contruvc the body and add it to the dynamics world
	btDefaultMotionState *ninjaMotionState = new btDefaultMotionState(ninjaTransform);

	//Colision shape
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));


	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar ninjaMass(1.0f);
	btVector3 ninjaInertia(0, 0, 0);

	DynamicRigidbodyComponent* ninjaRbComponent = new DynamicRigidbodyComponent(ninjaMotionState, newRigidShape, ninjaMass, ninjaInertia);
	ninja->addComponent(ninjaRbComponent);
	ninjaRbComponent->getRigidbody()->setRestitution(1);
	ninja->addComponent(new MouseComponent(mCamera));
	ninja->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent


	actors_.push_back(ninja);

	MoveCameraComponent* camMove = dynamic_cast<MoveCameraComponent*> (cam->getComponent(ComponentName::MOVE_CAMERA));

	camMove->setUpPlayer(ninja);
	cam->getNode()->setPosition(ninjaTransform.getOrigin().getX(), 147, ninjaTransform.getOrigin().getZ() + 300 + cam->getNode()->getPosition().z);

	//----------------------NINJA---------------------------------

	//----------------------SUELO---------------------------------
	srand((unsigned int)time(NULL));
	GameObject *planito = new GameObject(mSceneMgr);
	planito->getNode()->setPosition(Ogre::Vector3(50 - 300, -20, 50 - 300));
	planito->getNode()->setScale(Ogre::Vector3(500, 5, 500));
	planito->addComponent(new EntityComponent("Suelo.mesh"));
	actors_.push_back(planito);

	//MOTION STATE
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -1, 0));


	btDefaultMotionState *groundMotionState = new btDefaultMotionState(groundTransform);

	//COLLISION SHAPE
	//Creamos un plano en el origen.
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);//Offset de 1
	//Masa 0 -> Objeto estático. Masa infinita
	btScalar groundMass(0.); //the mass is 0, because the ground is immovable (static)
	btVector3 localGroundInertia(0, 0, 0);

	planito->addComponent(new RigidbodyComponent(groundMotionState, groundShape, groundMass, localGroundInertia));

	camMove->setUpCamera(mCamera);

	//----------------------SUELO---------------------------------

	//----------------------TORRE---------------------------------
	Torre = new GameObject(mSceneMgr);
	Torre->getNode()->setPosition(Ogre::Vector3((20 * 50) - 300, -20, (20 * 50) - 300));
	Torre->getNode()->setScale(Ogre::Vector3(5, 5, 5));
	Torre->addComponent(new EntityComponent("Torre.mesh"));

	/*material = MaterialManager.Singleton.Create(name + "Material", ResourceGroupManager.DEFAULT_RESOURCE_GROUP_NAME);
	material.GetTechnique(0).GetPass(0).CreateTextureUnitState(this.texture.Name);
	material.SetSceneBlending(SceneBlendType.SBT_TRANSPARENT_ALPHA);
	material.SetDepthCheckEnabled(false);*/

	billboardSet = mSceneMgr->createBillboardSet();
	billboardSet->setMaterialName("health");
	billboardSet->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
	billboardSet->setDefaultDimensions(25, 2);
	//billboardSet->setBillboardOrigin(BillboardOrigin::BBO_TOP_CENTER);
	billboard = billboardSet->createBillboard(Vector3::ZERO);
	billboard->setPosition(Vector3(0, 35, 0));
	Torre->getNode()->attachObject(billboardSet);

	TowerComponent* newTower = new TowerComponent();
	newTower->setTowerUI(billboardSet);
	newTower->setMainGameRef(this);
	Torre->addComponent(newTower);

	actors_.push_back(Torre);

	//----------------------TORRE---------------------------------

	//----------------------ARBOLES-------------------------------
	GenerarArboles();

	//----------------------ARBOLES-------------------------------

	//----------------------ENEMIGOS------------------------------
	NuevaOleada();

	//----------------------ENEMIGOS------------------------------

	//----------------------MENUs------------------------	
	menuPausa = new GameObject(mSceneMgr);
	menuPausa->addComponent(new MenuPausa());
	dynamic_cast<MenuPausa*> (menuPausa->getComponent(ComponentName::MENUPAUSA))->SetMainGameRef(this);

	actors_.push_back(menuPausa);

	/*Este objeto solo ha de crearse cuando el jugador haya muerto*/
	//----------------------MENU GAMEOVER------------------------	
	menuGO = new GameObject(mSceneMgr);
	menuGO->addComponent(new MenuGameOver());
	dynamic_cast<MenuGameOver*> (menuGO->getComponent(ComponentName::MENUGAMEOVER))->SetMainGameRef(this);

	actors_.push_back(menuGO);

	panelOleadas = new GameObject(mSceneMgr);
	panelOleadas->addComponent(new PanelOleada(OLEADA));
	dynamic_cast<PanelOleada*> (panelOleadas->getComponent(ComponentName::PANELOLEADA))->SetMainGameRef(this);

	actors_.push_back(panelOleadas);

	panelEnemigos = new GameObject(mSceneMgr);
	panelEnemigos->addComponent(new PanelOleada(NUM_ENEMIGOS));
	dynamic_cast<PanelOleada*> (panelEnemigos->getComponent(ComponentName::PANELOLEADA))->SetMainGameRef(this);

	actors_.push_back(panelEnemigos);

	//----------------------MENUs------------------------
}

void MainGame::GenerarArboles()
{
	int random = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			random = rand() % 101;
			int pos = (5 + rand() % 5);

			if (random % 6 == 0) {
				GameObject *arbol_ = new GameObject(mSceneMgr);
				arbol_->getNode()->setPosition(Ogre::Vector3((i * 50) - (150 + (rand() % 50)), -20, (j * 50) - (150 + (rand() % 50))));				
				arbol_->getNode()->setScale(Ogre::Vector3(5, 5, 5));
				random = rand() % 6;
				switch (random)
				{
				case 0:
					arbol_->addComponent(new EntityComponent("Arbol.mesh")); break;
				case 1:
					arbol_->addComponent(new EntityComponent("Arbol_new.mesh")); break;
				case 2:
					arbol_->addComponent(new EntityComponent("Arbol2.mesh")); break;
				case 3:
					arbol_->addComponent(new EntityComponent("Arbol3.mesh")); break;
				case 4:
					arbol_->addComponent(new EntityComponent("Arbol4.mesh")); break;
				case 5:
					arbol_->addComponent(new EntityComponent("Arbol5.mesh")); break;
				case 6:
					arbol_->addComponent(new EntityComponent("Bosque.mesh")); break;
				default:
					break;

				}
				actors_.push_back(arbol_);

			}
		}
	}
}


void MainGame::NuevaOleada(void)
{
	for (int i = 0; i < 3*oleadaActual; i++) {

		GameObject * enemigo = new GameObject(mSceneMgr);
		if (i % 3 == 0){
			enemigo->addComponent(new EntityComponent("bot2.mesh")); 
			enemigo->getNode()->setScale(1.8, 1.8, 1.8);
		}
		else{
			enemigo->addComponent(new EntityComponent("bot1.mesh"));
			enemigo->getNode()->setScale(0.8, 0.8, 0.8);
		}
		
		enemigo->getNode()->setPosition(Ogre::Vector3((rand() % 40 * 50) - 300, 0, (rand() % 40 * 50) - 300));

		btVector3 enemyInitialPosition(btVector3(enemigo->getNode()->getPosition().x, 0, enemigo->getNode()->getPosition().z));

		btTransform enemyTransform;
		enemyTransform.setIdentity();
		enemyTransform.setOrigin(enemyInitialPosition);

		btDefaultMotionState *enemyMotionState = new btDefaultMotionState(enemyTransform);

		//Colision shape
		btCollisionShape *EnemyRigidShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

		//set the mass of the object. a mass of "0" means that it is an immovable object
		btScalar enemyMass(1.0f);
		btVector3 enemyInertia(0, 0, 0);

		DynamicRigidbodyComponent* enemyRbComponent = new DynamicRigidbodyComponent(enemyMotionState, EnemyRigidShape, enemyMass, enemyInertia);
		enemigo->addComponent(enemyRbComponent);
		enemyRbComponent->getRigidbody()->setRestitution(1);
		
		billboardSet = mSceneMgr->createBillboardSet();
		billboardSet->setMaterialName("health");
		billboardSet->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
		billboardSet->setDefaultDimensions(100, 10);

		if (i % 3 == 0){
			enemigo->addComponent(new Enemigo(ENEMY2));
			Enemigo* enemyRef = dynamic_cast<Enemigo*> (enemigo->getComponent(ComponentName::ENEMY));
			enemyRef->setUpPlayer(ninja);
			enemyRef->setUpTower(Torre);
			enemyRef->setEnemyUI(billboardSet);
		}
		else{
			enemigo->addComponent(new Enemigo(ENEMY1));
			Enemigo* enemyRef = dynamic_cast<Enemigo*> (enemigo->getComponent(ComponentName::ENEMY));
			enemyRef->setUpPlayer(ninja);
			enemyRef->setUpTower(Torre);
			enemyRef->setEnemyUI(billboardSet);
		}
		

		billboard = billboardSet->createBillboard(Vector3::ZERO);
		billboard->setPosition(Vector3(0, 40, 0));
		enemigo->getNode()->attachObject(billboardSet);

		actors_.push_back(enemigo);
		numEnemigos++;
	}

}

void MainGame::DestroyGameObject(GameObject * obj){

	if (obj->getComponent(ComponentName::ENEMY) != NULL) {
		numEnemigos--;
	}
	//Llamada para quitarlo de los actores
	BaseApplication::quitaGameObject(obj);

	//Ahora quitamos el entity
	DynamicRigidbodyComponent * DRB = dynamic_cast <DynamicRigidbodyComponent *> (obj->getComponent(ComponentName::RIGIDBODY));

	if (DRB != nullptr){
		DRB->getRigidbody()->activate(false);
	}

	obj->getNode()->setVisible(false);	
}

void MainGame::createGUI() {

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	//FontManager& fM = FontManager::getSingleton();

	OverlayContainer* lifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "health"));


	lifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	lifeGUI->setPosition(0, 0);
	lifeGUI->setDimensions(300, 35);
	lifeGUI->setMaterialName("health"); // Optional background material 

	OverlayContainer* backLifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "backHealth"));

	backLifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	backLifeGUI->setPosition(0, 0);
	backLifeGUI->setDimensions(300, 35);
	backLifeGUI->setMaterialName("backHealth"); // Optional background material */

	// Create an overlay, and add the panel*/
	Overlay* overlay = overlayManager.create("OverlayPlayer");
	overlay->add2D(backLifeGUI);
	overlay->add2D(lifeGUI);

	ninja->addComponent(new UICanvas(lifeGUI, overlay));
	dynamic_cast<PlayerComponent*> (ninja->getComponent(ComponentName::PLAYER))->setPlayerUI();

}

//-------------------------------------------------------------------------------------
void MainGame::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();

	createGUI();

}


void MainGame::RestartGame()
{
	playIndex = 1;
	mShutDown = true;
	instance = NULL;
}

void MainGame::GoMainMenu()
{
	playIndex = 0;
	mShutDown = true;
	instance = NULL;
}

void MainGame::quitGame() {
	playIndex = -1;
	mShutDown = true;
}

void MainGame::setPauseStatus() {
	pause = !pause;
}

bool MainGame::getGameOverStatus() {
	return partidaTerminada;
}

bool MainGame::getPauseStatus() {
	return pause;
}

MainGame *MainGame::instance = 0;

MainGame *MainGame::getInstance()
{
	if (!instance)
		instance = new MainGame;
	return instance;

}

void MainGame::ShowGameOver()
{ 
	partidaTerminada = true;
	dynamic_cast<MenuGameOver*> (menuGO->getComponent(ComponentName::MENUGAMEOVER))->ShowMenu();
}

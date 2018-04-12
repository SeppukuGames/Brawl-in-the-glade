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
#include <time.h>
#include <iostream>
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

	//Crear el plano en Ogre
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity *entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode *groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("groundNode");

	groundNode->attachObject(entGround);

	//create the plane entity to the physics engine, and attach it to the node

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -50, 0)); //ESTO TIENE QUE SER ASÍ PORQUE SI: MAGIC NUMERITO 
	//LUEGO EN LOS COMENTARIOS LO RESUELVE

	btScalar groundMass(0.); //the mass is 0, because the ground is immovable (static)
	btVector3 localGroundInertia(0, 0, 0);

	btCollisionShape *groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
	btDefaultMotionState *groundMotionState = new btDefaultMotionState(groundTransform);

	groundShape->calculateLocalInertia(groundMass, localGroundInertia);

	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(groundMass, groundMotionState, groundShape, localGroundInertia);
	btRigidBody *groundBody = new btRigidBody(groundRBInfo);

	//add the body to the dynamics world
	physicsEngine->getDynamicsWorld()->addRigidBody(groundBody);


	for (int i = 0; i < 100; i++)
	{
		//CREAMOS UN CUBITO
		Ogre::Entity *entity = mSceneMgr->createEntity("suelo.mesh");

		btVector3 initialPosition(-20 + i*3, 300-i*3, 0);
		std::string physicsCubeName = std::to_string(i);
		Ogre::SceneNode *newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(physicsCubeName);
		newNode->attachObject(entity);
		newNode->setPosition(Ogre::Vector3(-100 + i * 10, 100, 0));
		//create the new shape, and tell the physics that is a Box
		btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));
		physicsEngine->getCollisionShapes().push_back(newRigidShape);

		//set the initial position and transform. For this demo, we set the tranform to be none
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));

		//set the mass of the object. a mass of "0" means that it is an immovable object
		btScalar mass = 0.1f;
		btVector3 localInertia(0, 0, 0);

		startTransform.setOrigin(initialPosition);
		newRigidShape->calculateLocalInertia(mass, localInertia);

		//actually contruvc the body and add it to the dynamics world
		btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
		btRigidBody *body = new btRigidBody(rbInfo);
		body->setRestitution(1);
		body->setUserPointer(newNode);

		physicsEngine->getDynamicsWorld()->addRigidBody(body);
		physicsEngine->trackRigidBodyWithName(body, physicsCubeName);
	}

	//Creamos entidades. DEBERIAMOS DAR NOMBRES A ENTIDADES Y NODOS
	/*
	GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);

	//Componentes que se añaden al Game Component
	OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5,5,5)));
	OgritoQueRota->addComponent(new Transform(Ogre::Vector3(1, 0, 0)));
	OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	actors_.push_back(OgritoQueRota);
	*/
	/*
	
	
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

	*/
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

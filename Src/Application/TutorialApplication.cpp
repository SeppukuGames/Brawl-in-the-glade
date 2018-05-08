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
#include <stdio.h>
#include "AnimationComponent.h"


#include <time.h>
#include <iostream>
#include "Enemigo.h"
#include "RigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
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
	GameObject * cam = new GameObject(mSceneMgr);
	SceneNode* camNode = cam->getNode();
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

	//Crear el plano en Ogre
	/*Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	//Creamos un plano de terreno (Rigidbody estático) y una Esfera que cae al plano (dynamic rigidbody)

	//Todos los rigidbody necesitan una referencia al collision shape.
	//Collision shape es UNICAMENTE	para colisiones. No tiene masa, inercia,etc.
	//Si hay muchos rigidbodies con la misma colision, es bueno utilizar el mismo collision shape.

	//---------------------PLANO---------------------------------

	//COMENTADO YA QUE SE HACE ABAJO CON TILES. LO HE DEJADO PARA PODER CONSULTAR LA ESTRUCTURA
	
	//Crear el plano en Ogre
	/*Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	GameObject *planito = new GameObject(mSceneMgr,"suelo");
	planito->addComponent(new EntityComponent("ground"));

	//PhysicsComponent

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

	actors_.push_back(planito);*/

	//---------------------PLANO---------------------------------

	//---------------------ESFERA---------------------------------
	/*GameObject *esfera = new GameObject(mSceneMgr,"esfera");
	esfera->addComponent(new EntityComponent("ogrehead.mesh"));
	esfera->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 initialPosition(0, 100, 0);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(initialPosition);


	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *fallMotionState = new btDefaultMotionState(startTransform);

	//Colision shape
	//Creamos la esfera de radio 1
	btCollisionShape* fallShape = new btSphereShape(1);
	//btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass(10.0f);
	btVector3 fallInertia(0, 0, 0);

	DynamicRigidbodyComponent* rbComponent = new DynamicRigidbodyComponent(fallMotionState, fallShape, mass, fallInertia);
	esfera->addComponent(rbComponent);

	rbComponent->getRigidbody()->setRestitution(1);

	actors_.push_back(esfera);

	*/
	/*
	EXPLICACIÓN DE BTRIGIDBODY::btRigidBodyConstructionInfo:
	SI QUEREMOS CREAR OBJETOS SIMILARES, UTILIZAMOS EL MISMO BTRIGIDBODYCONSTRUCTIONINFO, YA QUE
	SE COPIAN AL OBJETO QUE SE LO DAMOS
	*/

	//---------------------ESFERA---------------------------------

	GameObject* ninja = new GameObject(mSceneMgr);
	ninja->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
	ninja->addComponent(new EntityComponent("ninja.mesh")); //Ninja.mesh
	ninja->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
	
	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 ninjaInitialPosition(0, 50, 0);
	btTransform ninjaTransform;
	ninjaTransform.setIdentity();
	ninjaTransform.setOrigin(ninjaInitialPosition);


	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *ninjaMotionState = new btDefaultMotionState(ninjaTransform);

	//Colision shape
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(2.0f, 3.0f, 2.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar ninjaMass(10.0f);
	btVector3 ninjaInertia(0, 0, 0);

	DynamicRigidbodyComponent* ninjaRbComponent = new DynamicRigidbodyComponent(ninjaMotionState, newRigidShape, ninjaMass, ninjaInertia);
	ninja->addComponent(ninjaRbComponent);
	ninjaRbComponent->getRigidbody()->setRestitution(1);
	ninja->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent
	actors_.push_back(ninja);


	srand((unsigned int)time(NULL));

	
	int random = 0;
	int cont = 200;

	for (int i = 0; i < 40; i++){
		for (int j = 0; j < 40; j++){
			random = rand() % 101;
			//Game Component ahora es Game Object
			GameObject *planito = new GameObject(mSceneMgr);
			planito->getNode()->setPosition(Ogre::Vector3((i * 50) - 300, -20, (j * 50) - 300));
			planito->getNode()->setScale(Ogre::Vector3(5, 5, 5));

			if (j == 20 && i == 20){

				planito->addComponent(new EntityComponent("Torre.mesh"));
				std::cout << "Posicion de la torre: " << planito->getNode()->getPosition().x << ", " <<
					planito->getNode()->getPosition().y << ", " << planito->getNode()->getPosition().z << "\n";
				actors_.push_back(planito);
			}
			else{

				if (random % 6 == 0){
					planito->addComponent(new EntityComponent("arbol.mesh"));
					actors_.push_back(planito);
				}
				else{

					planito->addComponent(new EntityComponent("suelo.mesh"));

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

					actors_.push_back(planito);

				}
			}
		}
	}
	
	
	ObjFactory::initialize(mSceneMgr);

	//EnemyPrototype * ninja;//Prototipo del enemigo
	//Super útil
	/*for (int i = 0; i < 1; i++){
		ninja = ObjFactory::getTypeEnemy();
		ninja->getNode()->setPosition(Ogre::Vector3(Ogre::Real(i * 20), Ogre::Real(0), Ogre::Real(i * 20)));
		ninja->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
		actors_.push_back(ninja);
	}*/

	//20 a 4
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			//GameComponent a GameObject
			GameObject * enemigo = new GameObject(mSceneMgr);
			enemigo->getNode()->setScale(0.5, 0.5, 0.5);
			enemigo->getNode()->setPosition(Ogre::Vector3((rand() % 40 * 50) - 300, 0, (rand() % 40 * 50) - 300));

			enemigo->addComponent(new EntityComponent("ogrehead.mesh")); //Ninja.mesh
			enemigo->addComponent(new Enemigo());
			//enemigo->addComponent(new CollisionComponent());		//Da un lag de la hostia cuando los enemigos colisionan contra el suelo.
			//enemigo->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
			//enemigo->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent
			actors_.push_back(enemigo);
		}
	}
	
	
	
	
	
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


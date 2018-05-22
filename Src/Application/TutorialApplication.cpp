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
#include "TestCollisionComponent1.h"
#include "TestCollisionComponent2.h"

using namespace Ogre;

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------

//Borrar luz, cámara,
//TutorialApplication::~TutorialApplication(void)
//{
//	
//}

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

	actors_.push_back(planito);

	//---------------------PLANO---------------------------------

	//---------------------ESFERA---------------------------------
	*/
	GameObject *esfera = new GameObject(mSceneMgr,"esfera");
	esfera->addComponent(new EntityComponent("ogrehead.mesh"));
	esfera->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
	

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 initialPosition(-20, 40, 0);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(initialPosition);


	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *fallMotionState = new btDefaultMotionState(startTransform);

	//Colision shape
	//Creamos la esfera de radio 1
	btCollisionShape* fallShape = new btSphereShape(10);
	//btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass(10.0f);
	btVector3 fallInertia(0, 0, 0);

	DynamicRigidbodyComponent* rbComponent = new DynamicRigidbodyComponent(fallMotionState, fallShape, mass, fallInertia);
	esfera->addComponent(rbComponent);
	rbComponent->getRigidbody()->setRestitution(1);

	esfera->addComponent(new TestCollisionComponent1());

	actors_.push_back(esfera);


	




	GameObject *cabeza = new GameObject(mSceneMgr, "cabeza");
	cabeza->addComponent(new EntityComponent("ogrehead.mesh"));
	cabeza->getNode()->setScale(Ogre::Real(0.1), Ogre::Real(0.1), Ogre::Real(0.1));

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 initialPositionc(-20, 20, 0);
	btTransform startTransformc;
	startTransformc.setIdentity();
	startTransformc.setOrigin(initialPositionc);

	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *fallMotionStatec = new btDefaultMotionState(startTransformc);
	//Colision shape
	//Creamos la esfera de radio 1
	btCollisionShape* fallShapec = new btSphereShape(10);
	//btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar massc(10.0f);
	btVector3 fallInertiac(0, 0, 0);

	DynamicRigidbodyComponent* rbComponentc = new DynamicRigidbodyComponent(fallMotionStatec, fallShapec, massc, fallInertiac);
	cabeza->addComponent(rbComponentc);
	rbComponentc->getRigidbody()->setRestitution(1);
	rbComponentc->getRigidbody()->setLinearFactor(btVector3(0, 0, 0));
	rbComponentc->getRigidbody()->setAngularFactor(btVector3(0, 0, 0));


	cabeza->addComponent(new TestCollisionComponent2());

	actors_.push_back(cabeza);

	/*EXPLICACIÓN DE BTRIGIDBODY::btRigidBodyConstructionInfo:
>>>>>>> Colisiones
	SI QUEREMOS CREAR OBJETOS SIMILARES, UTILIZAMOS EL MISMO BTRIGIDBODYCONSTRUCTIONINFO, YA QUE
	SE COPIAN AL OBJETO QUE SE LO DAMOS
	*/

	//---------------------ESFERA---------------------------------

	ninja = new GameObject(mSceneMgr);
	ninja->getNode()->setScale(Ogre::Real(0.2), Ogre::Real(0.2), Ogre::Real(0.2));
	ninja->addComponent(new EntityComponent("ninja.mesh")); //Ninja.mesh
	ninja->addComponent(new AnimationComponent("Idle1")); //Le pasas una inicial, luego la cambias desde el input.
	

	//Motion state
	//set the initial position and transform. For this demo, we set the tranform to be none
	btVector3 ninjaInitialPosition(0, 0, 0);

	btTransform ninjaTransform;
	ninjaTransform.setIdentity();
	ninjaTransform.setOrigin(ninjaInitialPosition);


	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *ninjaMotionState = new btDefaultMotionState(ninjaTransform);

	//Colision shape
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 30.0f, 5.0f));


	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar ninjaMass(10.0f);
	btVector3 ninjaInertia(0, 0, 0);

	DynamicRigidbodyComponent* ninjaRbComponent = new DynamicRigidbodyComponent(ninjaMotionState, newRigidShape, ninjaMass, ninjaInertia);
	ninja->addComponent(ninjaRbComponent);
	ninjaRbComponent->getRigidbody()->setRestitution(1);
	ninja->addComponent(new MoveComponent());			//Debajo del animation porque lo usa ->Asumo que el enemy prototype tiene MoveComponent
	actors_.push_back(ninja);

	MoveCameraComponent* camMove = dynamic_cast<MoveCameraComponent*> (cam->getComponent(ComponentName::MOVE_CAMERA));

	cabeza->addComponent(new TestCollisionComponent2());


	camMove->setUpPlayer(ninja);

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
	//Torre
	GameObject *Torre = new GameObject(mSceneMgr);
	Torre->getNode()->setPosition(Ogre::Vector3((20 * 50) - 300, -20, (20 * 50) - 300));
	Torre->getNode()->setScale(Ogre::Vector3(5, 5, 5));
	Torre->addComponent(new EntityComponent("Torre.mesh"));
	actors_.push_back(Torre);
	
	//Arboles
	int random = 0;
	for (int i = 0; i < 40; i++){
		for (int j = 0; j < 40; j++){
			random = rand() % 101;			
			int pos = (5 + rand() % 5);
			
			if (random % 6 == 0){
				GameObject *arbol_ = new GameObject(mSceneMgr);				
				arbol_->getNode()->setPosition(Ogre::Vector3((i * 50) - (150 + (rand() % 50)), -20, (j * 50) - (150 + (rand() % 50))));				
				//Falta rotacion
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
	
	
	//ObjFactory::initialize(mSceneMgr);

	/*EnemyPrototype * ogro;//Prototipo del enemigo
	//Super útil
	for (int i = 0; i < 1; i++){
		ogro = ObjFactory::getTypeEnemy();
		ogro->getNode()->setPosition(Ogre::Vector3(Ogre::Real(i * 20), Ogre::Real(0), Ogre::Real(i * 20)));
		//ogro->addComponent(new MoveComponent());
		actors_.push_back(ogro); 
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


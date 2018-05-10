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
#include "Factory.h"

#include <time.h>
#include <iostream>
#include "Enemigo.h"


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
	//LA CÁMARA YA VIENE CREADA POR BASE APPLICATION, SOLO CREAMOS EL NODO
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


	//Creamos un plano de terreno (Rigidbody estático) y una Esfera que cae al plano (dynamic rigidbody)

	//Todos los rigidbody necesitan una referencia al collision shape.
	//Collision shape es UNICAMENTE	para colisiones. No tiene masa, inercia,etc.
	//Si hay muchos rigidbodies con la misma colision, es bueno utilizar el mismo collision shape.

	//---------------------PLANO---------------------------------

	//Crear el plano en Ogre
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity *entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	Ogre::SceneNode *groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("groundNode");

	groundNode->attachObject(entGround);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -1, 0));

	//Masa 0 -> Objeto estático. Masa infinita
	btScalar groundMass(0.); //the mass is 0, because the ground is immovable (static)
	btVector3 localGroundInertia(0, 0, 0);

	//Creamos un plano en el origen.
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);//Offset de 1
	btDefaultMotionState *groundMotionState = new btDefaultMotionState(groundTransform);

	//Añadimos rigidbodies con collision Shapes en la escena
	groundShape->calculateLocalInertia(groundMass, localGroundInertia);

	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(groundMass, groundMotionState, groundShape, localGroundInertia);
	btRigidBody* groundRigidBody = new btRigidBody(groundRBInfo);

	//Añadimos el suelo al mundo
	physicsEngine->getDynamicsWorld()->addRigidBody(groundRigidBody);

	//---------------------PLANO---------------------------------

	//---------------------ESFERA---------------------------------

	Ogre::Entity *entity = mSceneMgr->createEntity("ogrehead.mesh");

	btVector3 initialPosition(0, 100, 0);
	std::string physicsCubeName = "ogrito";
	Ogre::SceneNode *newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(physicsCubeName);
	newNode->setScale(0.1, 0.1, 0.1);
	newNode->attachObject(entity);

	//Creamos la esfera de radio 1
	btCollisionShape* fallShape = new btSphereShape(1);
	//btCollisionShape *newRigidShape = new btBoxShape(btVector3(5.0f, 1.0f, 5.0f));
	physicsEngine->getCollisionShapes().push_back(fallShape);

	//set the initial position and transform. For this demo, we set the tranform to be none
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(initialPosition);

	//actually contruvc the body and add it to the dynamics world
	//Esfera a 50 metros de altura
	btDefaultMotionState *fallMotionState = new btDefaultMotionState(startTransform);

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass(10.0f);
	btVector3 fallInertia(0, 0, 0);

	fallShape->calculateLocalInertia(mass, fallInertia);

	//Construimos el rigidbody y lo añadimos al mundo
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	fallRigidBody->setRestitution(1);
	fallRigidBody->setUserPointer(newNode);

	physicsEngine->getDynamicsWorld()->addRigidBody(fallRigidBody);
	physicsEngine->trackRigidBodyWithName(fallRigidBody, physicsCubeName);

	/*EXPLICACIÓN DE BTRIGIDBODY::btRigidBodyConstructionInfo:
	SI QUEREMOS CREAR OBJETOS SIMILARES, UTILIZAMOS EL MISMO BTRIGIDBODYCONSTRUCTIONINFO, YA QUE
	SE COPIAN AL OBJETO QUE SE LO DAMOS
	*/
	//---------------------ESFERA---------------------------------
	//Creamos entidades. DEBERIAMOS DAR NOMBRES A ENTIDADES Y NODOS
	/*
	GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);

	//Componentes que se añaden al Game Component
	OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5,5,5)));
	OgritoQueRota->addComponent(new Transform(Ogre::Vector3(1, 0, 0)));
	OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	actors_.push_back(OgritoQueRota);
	*/

	
	srand((unsigned int)time(NULL));

	
	int random = 0;
	/*for (int i = 0; i < 40; i++){
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
	}*/


	ObjFactory::initialize(mSceneMgr);

	EnemyPrototype * ogro;//Prototipo del enemigo
	//Super útil
	for (int i = 0; i < 1; i++){
		ogro = ObjFactory::getTypeEnemy();
		ogro->getNode()->setPosition(Ogre::Vector3((i * 20), 0, (i * 20)));
		//actors_.push_back(ogro);
		añadeGameObject(ogro);
	}

	
	/*
	GameComponent * ogro= new GameComponent(mSceneMgr);
=======
	GameComponent * ogro = new GameComponent(mSceneMgr);
>>>>>>> origin/CamaraBasica
	ogro->getNode()->setScale(Ogre::Vector3(0.5, 0.5, 0.55));

	//ogro->getNode()->addChild(camNode);	//Esto es para asociar la cámara a sinbad (no hace falta ahora)
	
	ogro->addComponent(new EntityComponent("ogrehead.mesh"));
	ogro->addComponent(new MoveComponent());
<<<<<<< HEAD
	actors_.push_back(ogro);*/

	//actors_.push_back(ogro);

	//20 a 4
	/*for (int i = 0; i < 2; i++){
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
}


TutorialApplication *TutorialApplication::instance = 0;

//Había conflicto aqui pero es igual lol
TutorialApplication *TutorialApplication::getInstance()
{
	if (!instance)
		instance = new TutorialApplication;
	return instance;

}


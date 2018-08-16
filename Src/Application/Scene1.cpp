#include "Scene1.h"



#include "GraphicManager.h"
#include "EntityComponent.h"
//#include "PrefabManager.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "GameManager.h"

using namespace Ogre;

Scene1::Scene1() : Scene()
{
}


//Método encargado de crear la escena
void Scene1::CreateScene()
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	CreateGameObjects();
}

void Scene1::CreateGameObjects(void)
{
	lectorXML_.Leer("../../escena1.xml");
	
	//Objetos de prueba
	/*
	GameObject* ogrito = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(95.0f)), Ogre::Vector3(0, 1, 0));
	ogrito->GetNode()->rotate(quat);
	actors.push_back(ogrito);
	*/
	/*
	GameObject * player = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	//actors.push_back(player);

	GameObject * gm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::GAMEMANAGERPREFAB);
	//actors.push_back(gm);

	//GameObject * boxStatic = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::MUROPREFAB);	

	GameObject * Lightobject = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::LIGHTPREFAB);
	//actors.push_back(Lightobject);

	/*GameObject * cameraObject = new GameObject("camera");
	cameraObject->GetNode()->setPosition(0, 0, 500);
	cameraObject->AddComponent(new CameraComponent(camera));
	camera = ((CameraComponent*)cameraObject->GetComponent(CAMERA))->GetCamera();
	actors.push_back(cameraObject);*/
	/*
	GameObject * tower = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::TOWERPREFAB);
	

	GameObject * enemy = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::ENEMYPREFAB);
	GameObject * enemy2 = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::ENEMYPREFAB);
	*/	
	

}


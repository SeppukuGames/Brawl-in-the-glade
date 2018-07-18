#include "Scene1.h"



#include "GraphicManager.h"
#include "EntityComponent.h"
#include "PrefabManager.h"
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
	//Objetos de prueba
	GameObject* ogrito = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	actors.push_back(ogrito);

	GameObject * gm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::GAMEMANAGERPREFAB);
	actors.push_back(gm);

	GameObject * boxStatic = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::MUROPREFAB);	

	GameObject * Lightobject = new GameObject("light");
	Lightobject->GetNode()->setPosition(0, 100, 0);

	Lightobject->AddComponent(new LightComponent());
	Lightobject->AddComponent(new CircleColliderComponent(50));
	Lightobject->AddComponent(new RigidbodyComponent(false, 10.0f));
	Lightobject->AddComponent(new PlayerComponent());
	Lightobject->AddComponent(new EntityComponent("ogrehead.mesh"));
	actors.push_back(Lightobject);

	/*GameObject * cameraObject = new GameObject("camera");
	cameraObject->GetNode()->setPosition(0, 0, 500);
	cameraObject->AddComponent(new CameraComponent(camera));
	camera = ((CameraComponent*)cameraObject->GetComponent(CAMERA))->GetCamera();
	actors.push_back(cameraObject);*/
	
	GameObject * cameraObject = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::MAINCAMERA);
	SetCamera(((CameraComponent*)cameraObject->GetComponent(CAMERA))->GetCamera());
	actors.push_back(cameraObject);
}


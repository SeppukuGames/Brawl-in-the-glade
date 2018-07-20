#include "Scene2.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <Box2D.h>

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

Scene2::Scene2() : Scene()
{
}



//Método encargado de crear la escena
void Scene2::CreateScene()
{
	//Creamos luz ambiental
	//sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	CreateGameObjects();
}

void Scene2::CreateGameObjects(void)
{
	//Objetos de prueba
	GameObject* ogrito = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	actors.push_back(ogrito);

	GameObject * gm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::GAMEMANAGERPREFAB);
	actors.push_back(gm);

	GameObject * boxStatic = new GameObject("muro");
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(20.0f)), Ogre::Vector3(0, 0, 1));
	boxStatic->GetNode()->setOrientation(quat);
	boxStatic->AddComponent(new EntityComponent("ogrehead.mesh"));
	boxStatic->AddComponent(new BoxColliderComponent(500, 50));
	actors.push_back(boxStatic);

	GameObject * Lightobject = new GameObject("light");
	Lightobject->GetNode()->setPosition(0, 100, 0);

	Lightobject->AddComponent(new LightComponent());
	Lightobject->AddComponent(new CircleColliderComponent(50));
	Lightobject->AddComponent(new RigidbodyComponent(false, 10.0f));
	Lightobject->AddComponent(new PlayerComponent());
	Lightobject->AddComponent(new EntityComponent("ogrehead.mesh"));
	actors.push_back(Lightobject);

	GameObject * cameraObject = new GameObject("camera");
	cameraObject->GetNode()->setPosition(0, 0, 500);
	cameraObject->AddComponent(new CameraComponent());
	camera = ((CameraComponent*)cameraObject->GetComponent(CAMERA))->GetCamera();
	actors.push_back(cameraObject);
}

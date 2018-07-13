#include "Scene1.h"

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

using namespace Ogre;

Scene1::Scene1() : Scene()
{
}

//Método encargado de crear la escena
void Scene1::CreateScene()
{
	CreateGameObjects();
}

void Scene1::CreateGameObjects(void)
{

	//Objetos de prueba
	GameObject* ogrito = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	actors.push_back(ogrito);

	GameObject * gm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::GAMEMANAGERPREFAB);
	actors.push_back(gm);

	GameObject * player = new GameObject(sceneMgr, "player");
	player->GetNode()->setPosition(0, 100, 0);
	player->AddComponent(new EntityComponent("ogrehead.mesh"));
	player->AddComponent(new CircleColliderComponent(50));
	player->AddComponent(new RigidbodyComponent(false,100.0f));
	player->AddComponent(new PlayerComponent());
	actors.push_back(player);

	GameObject * boxStatic = new GameObject(sceneMgr, "muro");
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(20.0f)), Ogre::Vector3(0, 0, 1));
	boxStatic->GetNode()->setOrientation(quat);
	boxStatic->AddComponent(new EntityComponent("ogrehead.mesh"));
	boxStatic->AddComponent(new BoxColliderComponent(500, 50));
	actors.push_back(boxStatic);



}


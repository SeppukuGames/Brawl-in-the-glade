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

//Método encargado de crear la escena
void PauseScene::CreateScene()
{
	CreateGameObjects();
}

bool PauseScene::Tick(double elapsed){

	if (!HandleInput())
		return false;

	Update(elapsed);

	if (!Render())
		return false;

	return true;
}


//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
void PauseScene::CreateGameObjects(void)
{
	//TODO: Panel con botones (Overlay)

	//Objeto de prueba
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
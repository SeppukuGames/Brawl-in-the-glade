#include "PauseScene.h"
#include "Scene.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <Box2D.h>

#include "GraphicManager.h"
#include "AudioManager.h"
#include "PrefabManager.h"

#include "EntityComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
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

	GameObject * pm = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::PAUSEMANAGERPREFAB);
	//actors.push_back(pm); //NO ES NECESARIO AÑADIR AQUI EL OBJETO A LA LISTA DE ACTORES, ESTÁ EN PREFAB MANAGER

	GameObject * A = PrefabManager::GetInstance()->CreateObject(PREFABTYPE::NINJAPREFAB);
	//actors.push_back(A);

	GameObject * cameraObject = new GameObject("camera");
	cameraObject->GetNode()->setPosition(0, 0, 500);
	cameraObject->AddComponent(new CameraComponent());
	camera = ((CameraComponent*)cameraObject->GetComponent(CAMERA))->GetCamera();
	actors.push_back(cameraObject);
}
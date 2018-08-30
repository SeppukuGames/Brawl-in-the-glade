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

//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
void PauseScene::CreateGameObjects(void)
{
	//TODO: Leer por XML
	//TODO: Panel con botones (Overlay)
	lectorXML_.Leer("../../pause.xml");
	
}
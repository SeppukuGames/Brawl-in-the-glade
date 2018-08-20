#include "MenuScene.h"

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

MenuScene::MenuScene() : Scene()
{
}



//Método encargado de crear la escena
void MenuScene::CreateScene()
{
	//Creamos luz ambiental
	//sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	CreateGameObjects();
}

void MenuScene::CreateGameObjects(void)
{
	lectorXML_.Leer("../../menu.xml");
}

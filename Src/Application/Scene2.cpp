#include "Scene2.h"

#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>

#include "GraphicManager.h"
#include "PrefabManager.h"
#include "EntityComponent.h"

using namespace Ogre;

Scene2::Scene2() : Scene()
{
}

//Método encargado de crear la escena
void Scene2::CreateScene()
{
	CreateGameObjects();
}

//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
void Scene2::CreateGameObjects(void)
{
	//Objeto de prueba
	GameObject* ogrito = new GameObject(sceneMgr,"Ogrito");
	ogrito->AddComponent(new EntityComponent("ogrehead.mesh")); //Ninja.mesh

	actors.push_back(ogrito);
}


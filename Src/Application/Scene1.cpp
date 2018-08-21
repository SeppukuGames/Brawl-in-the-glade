#include "Scene1.h"

//Ya no hacen falta, verdad?
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
	//TODO: ¿Se rompe la pausa?
	lectorXML_.Leer("../../escena1.xml"); 
}


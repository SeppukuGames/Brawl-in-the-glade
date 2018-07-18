#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <Box2D.h>
#include "BoxColliderComponent.h"

#include "PrefabManager.h"
#include "SceneManager.h"
#include "GameObject.h"

#include "GameManager.h"
#include "PauseManager.h"
#include "EntityComponent.h"
#include "AudioComponent.h"
#include "CameraComponent.h"

#pragma region Singleton  
PrefabManager* PrefabManager::instance = 0;

PrefabManager* PrefabManager::GetInstance()
{
	if (instance == 0)
		instance = new PrefabManager();

	return instance;
}

void PrefabManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}
#pragma endregion Singleton

GameObject* PrefabManager::CreateObject(PREFABTYPE prefabType){

	GameObject *gameObject = nullptr;

	//Distinguimos entre el tipo de enemigo
	switch (prefabType){

	//Ejemplos de prefab
		
	case OGROPREFAB:
		//Se crea el GameObject
		gameObject = new GameObject("Ogrito");

		//Se añaden los componentes correspondientes
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		break;

	case NINJAPREFAB:
		gameObject = new GameObject("Ninjita");
		gameObject->AddComponent(new EntityComponent("ninja.mesh"));
		break;

	case GAMEMANAGERPREFAB:
		gameObject = new GameObject("Game_Manager");
		gameObject->AddComponent(GameManager::GetInstance());
		gameObject->AddComponent(new AudioComponent("../../Media/Sounds/getout.ogg", true,false));
		gameObject->AddComponent(new AudioComponent("../../Media/Sounds/bell.wav", false, false));

		break;	

	case PAUSEMANAGERPREFAB:
		gameObject = new GameObject("Pause_Manager");
		gameObject->AddComponent(new PauseManager());
		break;

	case MUROPREFAB:
		gameObject = new GameObject("Muro");
		//Ogre::Quaternion quat;
		//quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(20.0f)), Ogre::Vector3(0, 0, 1));
		//gameObject->GetNode()->setOrientation(quat);
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		gameObject->AddComponent(new BoxColliderComponent(500, 50));
		break;

	case MAINCAMERA:
		gameObject = new GameObject("Main_Camera");
		Ogre::Camera* camera = SceneManager::GetInstance()->GetCurrentScene()->GetCamera();
		//gameObject->AddComponent(new BoxColliderComponent(1, 1));
		//gameObject->AddComponent(new RigidbodyComponent(false));
		gameObject->AddComponent(new CameraComponent(camera));
		break;
	}

	return gameObject;
}
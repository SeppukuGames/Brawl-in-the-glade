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
#include "PlayerComponent.h"
#include "LightComponent.h"
#include "AnimationComponent.h"
#include "CanvasComponent.h"
#include "StatsComponent.h"
#include "EnemyComponent.h"
#include "BulletComponent.h"

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
	Ogre::Quaternion quat;
	srand((unsigned int)time(NULL));
	int random;

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
		gameObject = new GameObject("Ninja");
		gameObject->SetTag("Player");
		gameObject->AddComponent(new EntityComponent("ninja.mesh"));
		gameObject->AddComponent(new BoxColliderComponent(25, 25));
		gameObject->AddComponent(new RigidbodyComponent(false, 1.0f));
		gameObject->AddComponent(new PlayerComponent());
		gameObject->AddComponent(new StatsComponent());
		gameObject->AddComponent(new CanvasComponent());
		SceneManager::GetInstance()->GetCurrentScene()->SetPlayer(gameObject);
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
		//BORRAR DE LA ESCENA
		gameObject = new GameObject("Muro");
		//Ogre::Quaternion quat;
		//quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(20.0f)), Ogre::Vector3(0, 0, 1));
		//gameObject->GetNode()->setOrientation(quat);
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		gameObject->AddComponent(new BoxColliderComponent(500, 50));
		break;

	case MAINCAMERA:
		gameObject = new GameObject("Main_Camera");
		gameObject->AddComponent(new CameraComponent());
		SceneManager::GetInstance()->GetCurrentScene()->SetCamera(((CameraComponent*)gameObject->GetComponent(CAMERA))->GetCamera());
		break;

	case LIGHTPREFAB:
		//BORRAR DE LA ESCENA
		gameObject = new GameObject("Light");
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));			//Quizá cambiarlo por otro mesh?
		gameObject->GetNode()->setPosition(100, 0, 100);
		quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(-55.0f)), Ogre::Vector3(1, 0, 0));
		gameObject->GetNode()->setOrientation(quat);
		gameObject->AddComponent(new LightComponent());
		break;

	case TOWERPREFAB:
		gameObject = new GameObject("Tower");
		gameObject->SetTag("Tower");
		gameObject->AddComponent(new EntityComponent("Torre.mesh"));
		gameObject->AddComponent(new BoxColliderComponent(35, 35));
		gameObject->AddComponent(new CanvasComponent());
		gameObject->AddComponent(new StatsComponent());
		SceneManager::GetInstance()->GetCurrentScene()->SetTower(gameObject);
		
		break;

	case ENEMYPREFAB:
		random = rand() % 2 + 1;
		EnemyText = "Enemy ";
		EnemyText += std::to_string(i);
		gameObject = new GameObject(EnemyText);
		gameObject->SetTag("Enemy");
		gameObject->AddComponent(new BoxColliderComponent(25, 25));
		gameObject->AddComponent(new RigidbodyComponent(false, 1.0f));
		if (random == 1)
			gameObject->AddComponent(new EnemyComponent(enemyType::ENEMY1));
		else if (random == 2)
			gameObject->AddComponent(new EnemyComponent(enemyType::ENEMY2));
		gameObject->AddComponent(new StatsComponent());
		gameObject->AddComponent(new CanvasComponent());
		GameManager::GetInstance()->AddEnemy();
		++i;
		break;

	case BULLETPREFAB:
		BulletText = "Bullet ";
		BulletText += std::to_string(j);
		gameObject = new GameObject(BulletText);
		gameObject->SetTag("Bullet");
		gameObject->GetNode()->setScale(.5, .5, .5);
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		gameObject->AddComponent(new BoxColliderComponent(5, 5));
		gameObject->AddComponent(new RigidbodyComponent(false, 0.5f));
		gameObject->AddComponent(new BulletComponent());
		j++;
		break;
	}

	SceneManager::GetInstance()->GetCurrentScene()->AddGameObject(gameObject);

	return gameObject;
}

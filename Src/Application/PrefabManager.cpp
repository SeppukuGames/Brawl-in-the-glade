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

	case PLAYERPREFAB:
		gameObject = new GameObject("Ninja");
		gameObject->SetTag("Player");
		gameObject->AddComponent(new EntityComponent("ninja.mesh"));
		gameObject->GetNode()->setScale(.5, .5, .5);		

		//TODO: ¿Alguna de estas NO está en el XML y debería estar?
		//gameObject->AddComponent(new BoxColliderComponent(25, 25));
		//gameObject->AddComponent(new RigidbodyComponent(false, 1.0f));
		//gameObject->AddComponent(new PlayerComponent());
		//gameObject->AddComponent(new StatsComponent());

		gameObject->AddComponent(new CanvasComponent());
		gameObject->AddComponent(new LightComponent());
		GameManager::GetInstance()->SetPlayer(gameObject);
		break;

	case GAMEMANAGERPREFAB:
		gameObject = new GameObject("Game_Manager");
		gameObject->SetTag("GameManager");
		
		gameObject->AddComponent(GameManager::GetInstance());
		gameObject->AddComponent(new AudioComponent("../../Media/Sounds/getout.ogg", true,false));
		gameObject->AddComponent(new AudioComponent("../../Media/Sounds/bell.wav", false, false));
		//insertObjectIntoCurrentScene(gameObject);


		break;	

	case PAUSEMANAGERPREFAB:
		gameObject = new GameObject("Pause_Manager");
		gameObject->AddComponent(new PauseManager());
		insertObjectIntoCurrentScene(gameObject); //Seguramente esté aqui el problema de la pausa
		//¿?¿?
		break;

	case SUELOPREFAB:
		//BORRAR DE LA ESCENA
		gameObject = new GameObject("Suelo");
		//Ogre::Quaternion quat;
		//quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(20.0f)), Ogre::Vector3(0, 0, 1));
		//gameObject->GetNode()->setOrientation(quat);
		gameObject->SetTag("Suelo");
		gameObject->AddComponent(new EntityComponent("suelo.mesh"));
		//gameObject->AddComponent(new BoxColliderComponent(500, 50));
		//insertObjectIntoCurrentScene(gameObject);

		break;

	case MAINCAMERA:
		gameObject = new GameObject("Main_Camera");
		gameObject->SetTag("Camara");
		gameObject->AddComponent(new CameraComponent());
		SceneManager::GetInstance()->GetCurrentScene()->SetCamera(((CameraComponent*)gameObject->GetComponent(CAMERA))->GetCamera());
		//insertObjectIntoCurrentScene(gameObject);

		break;

	case LIGHTPREFAB:
		//BORRAR DE LA ESCENA
		gameObject = new GameObject("Light");
		gameObject->SetTag("Luz");
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));		//Quizá cambiarlo por otro mesh? O que no tenga, directamente
		quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(-55.0f)), Ogre::Vector3(1, 0, 0));
		gameObject->GetNode()->setOrientation(quat);
		gameObject->AddComponent(new LightComponent());
		//insertObjectIntoCurrentScene(gameObject);

		break;

	case TOWERPREFAB:
		gameObject = new GameObject("Tower");
		gameObject->SetTag("Tower");
		gameObject->AddComponent(new EntityComponent("Torre.mesh"));		
		gameObject->GetNode()->setScale(10, 10, 10);		
		gameObject->AddComponent(new CanvasComponent());		
		GameManager::GetInstance()->SetTower(gameObject);
		//TODO: XML?
		//gameObject->AddComponent(new BoxColliderComponent(35, 35));
		break;


	case ENEMY1PREFAB:
		//Esto hay que hacerlo random, tanto la posición como el tipo de enemigo a spawnear
		gameObject = new GameObject("Enemy" + std::to_string(numEnemigos)); 
		gameObject->SetTag("Enemy");
		gameObject->AddComponent(new EntityComponent("bot1.mesh"));		
		gameObject->GetNode()->setScale(1.1, 1.1, 1.1);		
		gameObject->AddComponent(new CanvasComponent());


		GameManager::GetInstance()->AddEnemy();
		numEnemigos++;
		break;

	case ENEMY2PREFAB:
		//Esto hay que hacerlo random, tanto la posición como el tipo de enemigo a spawnear
		gameObject = new GameObject("Enemy" + std::to_string(numEnemigos));
		gameObject->SetTag("Enemy");
		gameObject->AddComponent(new EntityComponent("bot2.mesh"));
		gameObject->GetNode()->setScale(1.1, 1.1, 1.1);
		gameObject->AddComponent(new CanvasComponent());

		GameManager::GetInstance()->AddEnemy();
		numEnemigos++;
		break;

	case ARBOLPREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("arbol.mesh"));
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;
		break;

	case ARBOL_NEWPREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("Arbol_new.mesh"));
		
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;
		break;

	case ARBOL2PREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("Arbol2.mesh"));
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;
		break;

	case ARBOL3PREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("Arbol3.mesh"));
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;
		break;

	case ARBOL4PREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("Arbol4.mesh"));
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;
		break;

	case ARBOL5PREFAB:
		gameObject = new GameObject("Arbol" + numArboles);
		gameObject->SetTag("Arbol");
		gameObject->AddComponent(new EntityComponent("Arbol5.mesh"));
		gameObject->GetNode()->setScale(5, 10, 5);
		numArboles++;

	
	//REFERENCIA TEMPORAL, NO SE VA A USAR. o no debería, vamos.
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

		//insertObjectIntoCurrentScene(gameObject); //Este lo voy a dejar para el newwave. Hay que quitarlo cuando se hagan las oleadas por XML
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
		insertObjectIntoCurrentScene(gameObject);
		j++;

		break;
	case MENU:
		gameObject = new GameObject("Menu");
		gameObject->SetTag("Menu");
		break;
	}

	

	return gameObject;
}

//He hecho esto para añadir algunos objetos directamente con la funcionalidad del PrefabManager y otros
//Que se tienen que completar -de momento- con el XML se incluyen más tarde.
void PrefabManager::insertObjectIntoCurrentScene(GameObject* obj){ SceneManager::GetInstance()->GetCurrentScene()->AddGameObject(obj); }

//Método que reinicia los valores de "numArboles" y "numEnemigos"
void PrefabManager::resetNameInts(){
	numArboles = numEnemigos = 0;
}
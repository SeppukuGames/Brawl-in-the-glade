#include "PrefabManager.h"
#include "GraphicManager.h"
#include "PauseManager.h"
#include "GameManager.h"

#include "GameObject.h"
#include "EntityComponent.h"
#include "AudioComponent.h"

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

GameObject* PrefabManager::CreateObject(PREFABTYPE prefabType){

	GameObject *gameObject = nullptr;

	//Distinguimos entre el tipo de enemigo
	switch (prefabType){

	case OGRO:
		gameObject = new GameObject(GraphicManager::GetInstance()->GetSceneManager(), "Ogrito");
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		gameObject->GetNode()->setPosition(100, 5, 0);
		break;

	case NINJA:
		gameObject = new GameObject(GraphicManager::GetInstance()->GetSceneManager(), "Ninjita");
		gameObject->AddComponent(new EntityComponent("ninja.mesh"));
		gameObject->GetNode()->setPosition(0, 100, 0);
		break;

	case GAMEMANAGERPREFAB:
		gameObject = new GameObject(GraphicManager::GetInstance()->GetSceneManager(), "Game_Manager");
		gameObject->AddComponent(new GameManager());
		break;
	
	case PAUSEMANAGERPREFAB:
		gameObject = new GameObject(GraphicManager::GetInstance()->GetSceneManager(), "Pause_Manager");
		gameObject->AddComponent(new PauseManager());
		break;
	
	}

	return gameObject;

}
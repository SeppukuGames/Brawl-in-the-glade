#include "PrefabManager.h"
#include "SceneManager.h"
#include "GameObject.h"

#include "GameManager.h"
#include "EntityComponent.h"
#include "AudioComponent.h"

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

	case OGRO:
		gameObject = new GameObject(SceneManager::GetInstance()->GetCurrentScene()->GetSceneMgr(), "Ogrito");
		gameObject->AddComponent(new EntityComponent("ogrehead.mesh"));
		gameObject->GetNode()->setPosition(100, 5, 0);
		break;

	case NINJA:
		gameObject = new GameObject(SceneManager::GetInstance()->GetCurrentScene()->GetSceneMgr(), "Ninjita");
		gameObject->AddComponent(new EntityComponent("ninja.mesh"));
		gameObject->GetNode()->setPosition(0, 100, 0);
		break;

	case GAMEMANAGER:
		gameObject = new GameObject(SceneManager::GetInstance()->GetCurrentScene()->GetSceneMgr(), "Game_Manager");
		gameObject->AddComponent(new GameManager());
		//gameObject->AddComponent(new AudioComponent("../../Media/Sounds/getout.ogg", true));

		break;	
	}

	return gameObject;
}
#include "PrefabManager.h"
#include "GameObject.h"
#include "EntityComponent.h"
#include "GraphicManager.h"


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

GameObject* PrefabManager::CreateObject(int id){

	GameObject *gameObject = nullptr;

	//Distinguimos entre el tipo de enemigo
	switch (id){

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
	}

	return gameObject;

}
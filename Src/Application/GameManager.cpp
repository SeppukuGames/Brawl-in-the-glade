#include "GameManager.h"
#include "InputManager.h"
#include "SceneManager.h"

#pragma region Singleton  
/* Null, because instance will be initialized on demand. */
GameManager* GameManager::instance = 0;

GameManager* GameManager::GetInstance()
{
	if (instance == 0)
		instance = new GameManager();

	return instance;
}

void GameManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

void GameManager::Start(){
	timer = SceneManager::GetInstance()->GetTimer();
}

void GameManager::Update(double elapsed){

	//Testeo para comprobar Input y pausa
	//Al pulsar la tecla P, se va al estado de Pausa
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timer->getMilliseconds() > SceneManager::GetInstance()->GetNextSceneChange())
		SceneManager::GetInstance()->LoadPauseScene(PAUSESCENE);

}
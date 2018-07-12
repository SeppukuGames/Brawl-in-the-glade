#include "PauseManager.h"
#include "InputManager.h"
#include "SceneManager.h"

PauseManager::PauseManager(){

}

void PauseManager::Start(){
	timer = SceneManager::GetInstance()->GetTimer();
}

void PauseManager::Update(double elapsed){

	 if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timer->getMilliseconds() > SceneManager::GetInstance()->GetNextSceneChange())
		SceneManager::GetInstance()->UnloadPauseScene();

}
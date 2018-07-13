#include "GameManager.h"
#include "InputManager.h"
#include "SceneManager.h"

void GameManager::Start(){
	timer = SceneManager::GetInstance()->GetTimer();
}

void GameManager::Update(double elapsed){

	//Testeo para comprobar Input y pausa
	//Al pulsar la tecla P, se va al estado de Pausa
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timer->getMilliseconds() > SceneManager::GetInstance()->GetNextSceneChange())
		SceneManager::GetInstance()->LoadPauseScene(PAUSESCENE);

}
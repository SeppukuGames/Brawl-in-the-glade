#include "GameManager.h"
#include "InputManager.h"
#include "SceneManager.h"

void GameManager::Update(double elapsed){

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P)){
		SceneManager::GetInstance()->LoadScene(PAUSESCENE);

	}

}
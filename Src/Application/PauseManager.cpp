#include "PauseManager.h"
#include "InputManager.h"
#include "SceneManager.h"

PauseManager::PauseManager(){
	
}

void PauseManager::Start(){
	frameRate = 2000.0f;
	timer = SceneManager::GetInstance()->GetTimer();
	nextUpdate = timer->getMilliseconds() + frameRate;
}

void PauseManager::Update(double elapsed){

	double timerInMilisec = timer->getMilliseconds();

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timerInMilisec > nextUpdate){
		nextUpdate = timerInMilisec + frameRate;
		SceneManager::GetInstance()->LoadScene(NULLSCENE);
	}

}
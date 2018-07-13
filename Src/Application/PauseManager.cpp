#include "PauseManager.h"
#include "InputManager.h"
#include "SceneManager.h"

PauseManager::PauseManager(){

}

void PauseManager::Start(){
	timer = SceneManager::GetInstance()->GetTimer(); //Obtenemos el tiempo transcurrido
}

void PauseManager::Update(double elapsed){

	//Testeo para salir del estado de pausa
	//Al pulsar la tecla P se vuelve a la escena 1
	 if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timer->getMilliseconds() > SceneManager::GetInstance()->GetNextSceneChange())
		SceneManager::GetInstance()->UnloadPauseScene();

}
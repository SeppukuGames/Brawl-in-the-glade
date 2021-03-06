#include "GameManager.h"
#include "InputManager.h"
#include "SceneManager.h"


#include "Scene.h"

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
	numWave = 1;
	enemyWave = numEnemiesXML + (numWave * difficulty);
	enemyNumber = 0;
}

void GameManager::Update(double elapsed){

	//Testeo para comprobar Input y pausa
	//Al pulsar la tecla P, se va al estado de Pausa
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_P) && timer->getMilliseconds() > SceneManager::GetInstance()->GetNextSceneChange())
		SceneManager::GetInstance()->LoadPauseScene(PAUSESCENE);

	/*if (Input::GetInstance()->getKey(OIS::KeyCode::KC_T)) {
		PrefabManager::GetInstance()->resetNameInts();
		SceneManager::GetInstance()->LoadScene(GAMEOVERSCENE);
	}*/

	if (enemyNumber == 0){
		NewWave();
		numWave++;
		enemyWave = numEnemiesXML + (numWave * difficulty);
	}
}

void GameManager::SetPlayer(GameObject* _player) {
	player = _player;
}

void GameManager::SetTower(GameObject* _tower) {
	tower = _tower;
}

void GameManager::NewWave(){

	int cont = 0;
	while (enemyNumber < enemyWave){
				SceneManager::GetInstance()->GetCurrentScene()->CreateEnemies(enemyNumber % 2);
	}
}
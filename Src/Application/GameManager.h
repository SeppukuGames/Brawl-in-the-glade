#ifndef __GameManager_h_
#define __GameManager_h_

#include "Component.h"
#include "Ogre.h"


//Clase encargada de gestionar el estado de la escena
class GameManager : public Component{

#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static GameManager *instance;

public:
	/* Static access method. */
	static GameManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

#pragma region Attributes  
private:
	Ogre::Timer* timer;

	int enemyNumber;	//Contador de n�mero de enemigos restantes
	int enemyWave;		//Contador de n�mero de enemigos por ronda
	int numWave;		// La oleada en la que nos encontramos		
	int numEnemiesXML;	// numero de enemigos determinado por el XML
	int waveNumber;		//Contador de rondas
	float difficulty;
	

	GameObject* player;								//Atributo para la referencia del jugador principal
	GameObject* tower;								//Atributo para la referencia a la torre

#pragma endregion Attributes

#pragma region Methods  

public:
	virtual void Start();
	virtual void Update(double elapsed);

	virtual ~GameManager(){ instance = 0; };

	GameObject * GetPlayer() { return player; };
	void SetPlayer(GameObject* player);
	GameObject * GetTower() { return tower; };
	void SetTower(GameObject* tower);
	
	void AddEnemy(){ enemyNumber++; };
	void RemoveEnemy(){ enemyNumber--; };
	void setDifficulty(float difficulty) { this->difficulty = difficulty; };
	void setnumEnemiesXML(int num) { numEnemiesXML = num; };
	int GetWaveNumber() { return waveNumber; };
	int GetEnemyNumber() { return enemyNumber; };
	void NewWave();
private:
	GameManager(){  };


#pragma endregion Methods

};

#endif /* __GameManager_h_ */
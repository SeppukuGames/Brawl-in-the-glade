#ifndef _PREFABMANAGER_H_
#define _PREFABMANAGER_H_

#include "GameObject.h"

//Enumerado pra los tipos de objetos que se pueden crear
enum PREFABTYPE{ OGROPREFAB, PLAYERPREFAB, GAMEMANAGERPREFAB,PAUSEMANAGERPREFAB, MUROPREFAB, MAINCAMERA, LIGHTPREFAB, TOWERPREFAB,
ENEMYPREFAB, NULO};

class PrefabManager {
#pragma region Singleton  

private:
	static PrefabManager  *instance;
	int i = 0;

public:
	static PrefabManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	//Constructora privada para prevenir instanciación 
	PrefabManager(){};
	PrefabManager::~PrefabManager(){};

public:
	//Método para crear un GameObject u otro dependiendo del tipo de prefab recibido
	GameObject * CreateObject(PREFABTYPE prefabType);
};

#endif /* _PREFAB_H_ */

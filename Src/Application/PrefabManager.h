#ifndef _PREFABMANAGER_H_
#define _PREFABMANAGER_H_

#include "GameObject.h"

//Enumerado pra los tipos de objetos que se pueden crear
enum PREFABTYPE{ OGROPREFAB, NINJAPREFAB, GAMEMANAGERPREFAB,PAUSEMANAGERPREFAB, MUROPREFAB, MAINCAMERA, LIGHTPREFAB };

class PrefabManager {
#pragma region Singleton  

private:
	static PrefabManager  *instance;

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

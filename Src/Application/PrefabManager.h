#ifndef _PREFABMANAGER_H_
#define _PREFABMANAGER_H_

#include "GameObject.h"

enum PREFABTYPE{ OGRO, NINJA, GAMEMANAGER };

class PrefabManager {
#pragma region Singleton  

private:
	static PrefabManager  *instance;

public:
	static PrefabManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	PrefabManager(){};
	PrefabManager::~PrefabManager(){};

public:
	//Método para crear un GameObject u otro dependiendo del id recibido (0 si ogro, 1 si ninja) Este id se cambiará por un enum seguramente
	GameObject * CreateObject(PREFABTYPE prefabType);
};

#endif /* _PREFAB_H_ */

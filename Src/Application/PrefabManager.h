#ifndef _PREFABMANAGER_H_
#define _PREFABMANAGER_H_

#include "GameObject.h"

//Enumerado pra los tipos de objetos que se pueden crear

//Merge: añadido bulletprefab al enum de lectorXML
enum PREFABTYPE{
	OGROPREFAB, PLAYERPREFAB, GAMEMANAGERPREFAB, PAUSEMANAGERPREFAB, MUROPREFAB, MAINCAMERA, LIGHTPREFAB, TOWERPREFAB, BULLETPREFAB,
	ENEMY1PREFAB, ENEMY2PREFAB, ARBOLPREFAB, ARBOL_NEWPREFAB, ARBOL2PREFAB, ARBOL3PREFAB, ARBOL4PREFAB, ARBOL5PREFAB, NULO,
	ENEMYPREFAB /*Para corregir rapidamente lo del newwave*/,MENU
};


class PrefabManager {
#pragma region Singleton  

private:
	static PrefabManager  *instance;

public:
	static PrefabManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

#pragma region Attributes
private:
	int numEnemigos = 0, numArboles = 0;
	int i = 0;
	int j = 0;
	std::string EnemyText, BulletText;

#pragma endregion Attributes

private:
	//Constructora privada para prevenir instanciación 
	PrefabManager(){};
	PrefabManager::~PrefabManager(){};

	

public:
	//Método para crear un GameObject u otro dependiendo del tipo de prefab recibido
	GameObject * CreateObject(PREFABTYPE prefabType);
	void insertObjectIntoCurrentScene(GameObject*);
	void resetNameInt();
};

#endif /* _PREFAB_H_ */

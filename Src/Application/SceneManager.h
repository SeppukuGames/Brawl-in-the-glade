#ifndef __SceneManager_h_
#define __SceneManager_h_

#include <OgreTimer.h>
#include <stack>
#include "Scene.h"

enum SceneType {MENUSCENE,SCENE1, SCENE2, GAMEOVERSCENE};

class SceneManager
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static SceneManager *instance;

	/* Private constructor to prevent instancing. */
	SceneManager();

	~SceneManager();

public:
	/* Static access method. */
	static SceneManager * GetInstance();

	static void ResetInstance();
#pragma endregion Singleton

private:
	//Para el bucle principal
	double lastTime;
	Ogre::Timer *timer;

	Ogre::RenderWindow* window;

	std::stack<Scene*> scenes;
	SceneType sceneType;
	

public:
	void Go();

	//Carga la escena correspondiente
	void LoadScene(SceneType sceneType);

	void LoadPauseScene();
	void UnloadPauseScene();

private:
	bool GameLoop();

	//Métodos para el cambio de escenas
	void ChangeScene(Scene * scene);
	void PushScene(Scene * scene);
	void PopScene();
};
#endif // #ifndef __SceneManager_h_


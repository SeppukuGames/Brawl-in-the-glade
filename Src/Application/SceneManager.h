#ifndef __SceneManager_h_
#define __SceneManager_h_

#include <OgreTimer.h>
#include <stack>
#include "Scene.h"

enum SceneType {NULLSCENE, MENUSCENE, PAUSESCENE, SCENE1, SCENE2, GAMEOVERSCENE};

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

	bool deleteScene;
	bool isPaused;
	

public:
	void Go();

	void LoadScene(SceneType sceneType){
		deleteScene = true;
		this->sceneType = sceneType;
	};

	void UnloadPauseScene();

	
	/* Static access method. */
	inline Ogre::Timer* GetTimer(){ return timer; };
	inline double GetLastTime(){ return lastTime; };

	

private:
	bool GameLoop();

	void LoadPauseScene(Scene * scene);
	void SetScene(SceneType sceneType);

	//Métodos para el cambio de escenas
	void ChangeScene(Scene * scene);
	void PushScene(Scene * scene);
	void PopScene();
};
#endif // #ifndef __SceneManager_h_


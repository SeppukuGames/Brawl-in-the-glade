#ifndef __SceneManager_h_
#define __SceneManager_h_

#include <OgreTimer.h>
#include <stack>
#include "Scene.h"

#define SCENEWAIT 2000

enum SceneType {NULLSCENE, MENUSCENE,SCENE1, SCENE2, GAMEOVERSCENE};
enum PauseSceneType {NULLPAUSESCENE, PAUSESCENE };

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

	bool deleteScene;
	bool isPaused;

	//Segundo en el que se permite cambiar de escena
	double nextSceneChange;
public:
	void Go();

	//Carga la escena correspondiente
	void LoadScene(SceneType sceneType);
	void LoadPauseScene(PauseSceneType pauseSceneType);
	void UnloadPauseScene();

	inline Scene* GetCurrentScene(){ return scenes.top(); };
	inline Ogre::Timer* GetTimer(){ return timer; };
	inline double GetLastTime(){ return lastTime; };

	inline double GetNextSceneChange(){ return nextSceneChange; };
	inline double SetNextSceneChange(double next){ nextSceneChange = next; };

private:
	bool GameLoop();

	void SetScene(SceneType sceneType);

	//Métodos para el cambio de escenas
	void ChangeScene(Scene * scene);
	void PushScene(Scene * scene);
	void PopScene();
};
#endif // #ifndef __SceneManager_h_


#ifndef __SceneManager_h_
#define __SceneManager_h_

#include <OgreTimer.h>
#include <stack>
#include "Scene.h"

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

public:
	void Go();

private:
	bool GameLoop();

	void PushScene(Scene * scene);
	void PopScene();
};
#endif // #ifndef __SceneManager_h_


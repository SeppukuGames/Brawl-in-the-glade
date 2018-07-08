#include "SceneManager.h"
#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>

#include "GraphicManager.h"
#include "Scene1.h"
#include "Scene2.h"

#pragma region Singleton  
/* Null, because instance will be initialized on demand. */
SceneManager* SceneManager::instance = 0;

SceneManager* SceneManager::GetInstance()
{
	if (instance == 0)
		instance = new SceneManager();

	return instance;
}

void SceneManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

SceneManager::SceneManager() :
timer(0),
lastTime(0)
{
}


SceneManager::~SceneManager()
{
	delete timer;
	
	while (!scenes.empty())
	{
		Scene * scene = scenes.top();
		scenes.pop();
		delete scene;
	}
}

void SceneManager::Go()
{
	window = GraphicManager::GetInstance()->GetWindow();

	timer = new Ogre::Timer();
	lastTime = timer->getMilliseconds();

	PushScene(new Scene1());
	//PushScene(new Scene2());

	while (GameLoop());
}

// Bucle principal.Acaba cuando se cierra la ventana o un error en renderOneFrame
bool SceneManager::GameLoop()
{
	//Actualiza el RenderWindow
	Ogre::WindowEventUtilities::messagePump();

	if (window->isClosed())
		return false;

	double current = timer->getMilliseconds();
	double elapsed = (current - lastTime) / 1000;

	if (!(scenes.top())->Tick(elapsed))
		return false;

	lastTime = current;

	return true;
}

void SceneManager::PushScene(Scene * scene)
{
	if (scenes.size() > 0)
		GraphicManager::GetInstance()->GetWindow()->removeAllViewports();

	scenes.push(scene);
	scene->SetViewport();
}

void SceneManager::PopScene()
{
	if (scenes.size() > 0)
	{
		Scene * scene = scenes.top();
		scenes.pop();
		delete (scene);
		GraphicManager::GetInstance()->GetWindow()->removeAllViewports();

		if (scenes.size() > 0)
			scenes.top()->SetViewport();
	}
}
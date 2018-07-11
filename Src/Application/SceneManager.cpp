#include "SceneManager.h"
#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>

#include "GraphicManager.h"
#include "Scene1.h"
#include "Scene2.h"
#include "PauseScene.h"

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
lastTime(0),
deleteScene(false),
sceneType(NULLSCENE)
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
	sceneType = SCENE1; //TODO: cambiar a MENUSCENE cuando haya menú
	SetScene(sceneType);

	while (GameLoop());
}

#pragma region Carga y descarga de escenas  


//Método encargado de crear las distintas escenas. Es llamado desde el resto de escenas (Callback de botones, teclas, ect)
void SceneManager::SetScene(SceneType sceneType){
	Scene * scene;
	isPaused = false;
	switch (sceneType){

	case SCENE1:
		scene = new Scene1();
		break;

	case SCENE2:
		scene = new Scene2();
		break;

	case PAUSESCENE:
		scene = new PauseScene();
		isPaused = true;
		break;

	case MENUSCENE:
		//scene = new MenuScene();
		break;

	case GAMEOVERSCENE:
		//scene = new GameOverScene();
		break;

	//Se accede aquí cuando se sale del Estado pausa
	case NULLSCENE:
		UnloadPauseScene();
	}

	//Si el estado es pausa, no se cambia de escena, solo se elimina y se sigue con Scene1
	if (sceneType != NULLSCENE){
		if (!isPaused)
			ChangeScene(scene);
		else
			LoadPauseScene(scene);

	}
	deleteScene = false;
	sceneType = NULLSCENE;
}

//Carga la escena de pausa sin eliminar la escena anterior
void SceneManager::LoadPauseScene(Scene * scene){
	PushScene(scene);
}

//Elimina la escena de pausa y se seguirá ejecutando la escena de juego
void SceneManager::UnloadPauseScene(){
	PopScene();
}

// Bucle principal.Acaba cuando se cierra la ventana u ocurre un error en renderOneFrame
bool SceneManager::GameLoop()
{
	if (deleteScene)
		SetScene(sceneType);

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

//Método que elimina la escena anterior y carga la nueva
void SceneManager::ChangeScene(Scene * scene){
	PopScene();
	PushScene(scene);
}

//Método que carga una escena
void SceneManager::PushScene(Scene * scene)
{
	if (scenes.size() > 0)
		GraphicManager::GetInstance()->GetWindow()->removeAllViewports();

	scenes.push(scene);
	scene->SetViewport();
}

//Método que elimina la escena anterior
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

#pragma endregion Carga y descarga de escenas

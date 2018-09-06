#include "SceneManager.h"
#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>
#include <iostream>

#include "GraphicManager.h"
#include "AudioManager.h"
#include "Scene1.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "AudioComponent.h"
#include "Error.h"

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
lastTime(0), 
timer(0),
deleteScene(false),
sceneType(NULLSCENE),
isPaused(false)
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

//Inicializa el SceneManager
void SceneManager::Go()
{
	window = GraphicManager::GetInstance()->GetWindow();

	timer = new Ogre::Timer();
	lastTime = timer->getMilliseconds();
	nextSceneChange = timer->getMilliseconds() + SCENEWAIT;

	sceneType = MENUSCENE;
	SetScene();
	std::cout << "Terminado de cargar escena" << endl;
	while (GameLoop());
}

#pragma region Carga y descarga de escenas  

//Establece que hay que cambiar de escena en la siguiente vuelta de bucle
void SceneManager::LoadScene(SceneType sceneType){
	deleteScene = true;
	this->sceneType = sceneType;
}

//Carga la escena de pausa sin eliminar la escena anterior
void SceneManager::LoadPauseScene(PauseSceneType pauseSceneType){
	Scene * scn;

	switch (pauseSceneType)
	{
	case PAUSESCENE:
		scn = new PauseScene();
	
		break;

	default:
		//En caso de insertar un nombre de escena de pausa no existente, lanzamos un error
		Error errorE("Escena de pausa no existente");
		throw errorE;
		break;
	}

	SceneManager::GetInstance()->GetCurrentScene()->setStopUpdate(true);	//Paramos la actualización del Scene1
	GraphicManager::GetInstance()->GetWindow()->removeAllViewports();		//Eliminamos todos los viewports
	AudioManager::GetInstance()->Pause();									//Paramos todos los sonidos de la escena

	PushScene(scn);
	isPaused = true;

	nextSceneChange = timer->getMilliseconds() + SCENEWAIT;
}

//Establece que se tiene que borrar la escena de Pausa en la siguiete vuelta de bucle
void SceneManager::UnloadPauseScene(){
	deleteScene = true;
	nextSceneChange = timer->getMilliseconds() + SCENEWAIT;
}

// Bucle principal. Comprueba en cada vuelta si hay que cambiar de escena
bool SceneManager::GameLoop()
{
	//Comprueba si hay que cambiar de escena y la cambia
	CheckChangeScene();

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
//Comprueba si se tiene que cambiar de escena y ejecuta en caso de tener que hacerlo
void SceneManager::CheckChangeScene(){

	if (deleteScene)
	{
		//Caso en el que la escena de pausa está activa
		if (isPaused)
		{
			PopScene();
			scenes.top()->SetViewport();
			isPaused = false;
			AudioManager::GetInstance()->Resume();		//Volvemos a reanudar los sonidos al salir de la escena de Pausa
		}
		else
			SetScene();

		deleteScene = false;
	}
}

//Método encargado de crear las distintas escenas
void SceneManager::SetScene(){
	Scene * scene;

	switch (sceneType){

	case SCENE1:
		scene = new Scene1();
		break;

	case MENUSCENE:
		scene = new MenuScene();
		break;

	case GAMEOVERSCENE:
		scene = new GameOverScene();
		break;

	default:
		Error errorE("Escena no existente");
		throw errorE;
		break;

	}

	ChangeScene(scene);
	sceneType = NULLSCENE;
}

//Método que elimina las escenas actuales y carga una nueva
void SceneManager::ChangeScene(Scene * scene){
	while (!scenes.empty())
		PopScene();

	PushScene(scene);
}

//Método que carga una escena
void SceneManager::PushScene(Scene * scene)
{
	scenes.push(scene);
	scene->CreateScene();
	scene->SetViewport();
}

//Método que elimina la escena anterior
void SceneManager::PopScene()
{
	Scene * scene = scenes.top();
	scenes.pop();
	delete (scene);
	GraphicManager::GetInstance()->GetWindow()->removeAllViewports();
}

#pragma endregion Carga y descarga de escenas

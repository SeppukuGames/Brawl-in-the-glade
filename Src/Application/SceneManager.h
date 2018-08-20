#ifndef __SceneManager_h_
#define __SceneManager_h_

#include <OgreTimer.h>
#include <stack>
#include "Scene.h"

#define SCENEWAIT 1000		//Tiempo de espera para cambiar de escena

//Enumerados para los tipos de escena normal y escena de pausa
enum SceneType {NULLSCENE, MENUSCENE,SCENE1, /*SCENE2,*/ GAMEOVERSCENE};
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
	double lastTime;				//Atributo para el bucle principal

	Ogre::Timer *timer;				//Contandor principal del juego

	Ogre::RenderWindow* window;		//Referencia a la ventana

	std::stack<Scene*> scenes;		//Pila de escenas
	SceneType sceneType;			//Escena nueva que se va a insertar en la siguiente vuelta de bucle

	bool deleteScene;				//Guarda si se tiene que cambiar de escena en la siguiente vuelta de bucle
	bool isPaused;					//Guarda si la escena que se cambia es Pausa

	double nextSceneChange;			//Atributo que indica el segundo en el que se permite cambiar de escena

public:
	void Go();	//Inicializa el SceneManager

	void LoadScene(SceneType sceneType);					//Establece que hay que cambiar de escena en la siguiente vuelta de bucle			

	//Pausa
	void LoadPauseScene(PauseSceneType pauseSceneType);		//Carga la escena de pausa sin eliminar la escena anterior
	void UnloadPauseScene();								//Establece que se tiene que borrar la escena de Pausa en la siguiete vuelta de bucle

	//Getters
	inline Scene* GetCurrentScene(){ return scenes.top(); };	//Devuelve la escena actual
	inline Ogre::Timer* GetTimer(){ return timer; };			//Devuelve el timer
	inline double GetLastTime(){ return lastTime; };			//Devuelve el el tiempo anterior

	inline double GetNextSceneChange(){ return nextSceneChange; };					//Devuelve la siguiente escena a cambiar
	inline double SetNextSceneChange(double next){ nextSceneChange = next; };		//Establece la siguiente escena a cambiar

private:
	bool GameLoop();					// Bucle principal. Comprueba en cada vuelta si hay que cambiar de escena

	//Métodos para el cambio de escenas
	void CheckChangeScene();			//Comprueba si se tiene que cambiar de escena y ejecuta en caso de tener que hacerlo
	void SetScene();					//Método encargado de crear las distintas escenas

	void ChangeScene(Scene * scene);	//Método que elimina las escenas actuales y carga una nueva
	void PushScene(Scene * scene);		//Método que carga una escena
	void PopScene();					//Método que elimina la escena anterior
};
#endif // #ifndef __SceneManager_h_


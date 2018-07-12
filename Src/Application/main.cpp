#include <iostream>
#include "checkML.h"
#include "GraphicManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "PrefabManager.h"
#include "SceneManager.h"
#include "Error.h"

#ifdef _DEBUG 
int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detector de basura
	_CrtDumpMemoryLeaks();// para que muestre la basura
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
#endif
	GraphicManager * graphicManager;
	Input * input;
	AudioManager * audioManager;
	PhysicsManager * physicsManager;
	PrefabManager * prefabManager;
	SceneManager * sceneManager;


	try{
		graphicManager = GraphicManager::GetInstance();				//Inicializa Ogre
		graphicManager->InitGraphics();

		input = Input::GetInstance();								//Inicializa el input (OIS)
		input->initInput();

		audioManager = AudioManager::GetInstance();					//Inicializa el motor de audio
		audioManager->InitSoundEngine();

		physicsManager = PhysicsManager::GetInstance();				//Inicializa el motor de física
		physicsManager->InitPhysics();

		prefabManager = PrefabManager::GetInstance();				//Inicializa el PrefabManager

		sceneManager = SceneManager::GetInstance();					//Inicializa Gestor de escenas

		//Empieza el juego
		sceneManager->Go();

		sceneManager->ResetInstance();									//Destruye Gestor de escenas
		prefabManager->ResetInstance();
		physicsManager->ResetInstance();
		audioManager->ResetInstance();									//Destruye el motor de audio
		input->ResetInstance();
		graphicManager->ResetInstance();								//Destruye Ogre

	}
	catch (Error &e){
		sceneManager->ResetInstance();									//Destruye Gestor de escenas
		prefabManager->ResetInstance();
		physicsManager->ResetInstance();
		audioManager->ResetInstance();									//Destruye el motor de audio
		input->ResetInstance();
		graphicManager->ResetInstance();								//Destruye Ogre

		//Mostrar mensaje
		std::cout << e.mensaje().c_str();
		cin.ignore();
		system("PAUSE");
	}

	return 0;
}

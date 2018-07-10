#include <iostream>
#include "checkML.h"
#include "Error.h"
#include "GraphicManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"


#ifdef _DEBUG 
int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detector de basura
	_CrtDumpMemoryLeaks();// para que muestre la basura
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
#endif
	GraphicManager * graphicManager;
	Input * input;
	PhysicsManager * physicsManager;
	SceneManager * sceneManager;


	try{
		graphicManager = GraphicManager::GetInstance();				//Inicializa Ogre
		graphicManager->InitGraphics();

		input = Input::GetInstance();								//Inicializa el input (OIS)
		input->initInput();

		physicsManager = PhysicsManager::GetInstance();
		physicsManager->InitPhysics();

		sceneManager = SceneManager::GetInstance();					//Inicializa Gestor de escenas

		//Empieza el juego
		sceneManager->Go();

		sceneManager->ResetInstance();									//Destruye Gestor de escenas
		physicsManager->ResetInstance();
		input->ResetInstance();
		graphicManager->ResetInstance();								//Destruye Ogre

	}
	catch (Error &e){
		sceneManager->ResetInstance();									//Destruye Gestor de escenas
		physicsManager->ResetInstance();
		input->ResetInstance();
		graphicManager->ResetInstance();								//Destruye Ogre

		//Mostrar mensaje
		std::cout << e.mensaje().c_str();
		cin.ignore();
		system("PAUSE");

	}

	
	return 0;
}

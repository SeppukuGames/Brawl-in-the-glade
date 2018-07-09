#include <iostream>
#include "GraphicManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#ifdef _DEBUG 
int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detector de basura
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
#endif

	GraphicManager * graphicManager = GraphicManager::GetInstance();	//Inicializa Ogre
	graphicManager->InitGraphics();


	Input * input = Input::GetInstance();								//Inicializa el input (OIS)
	input->initInput();

	SceneManager * sceneManager = SceneManager::GetInstance();			//Inicializa Gestor de escenas
	

	//Empieza el juego
	sceneManager->Go();

	sceneManager->ResetInstance();										//Destruye Gestor de escenas
	graphicManager->ResetInstance();									//Destruye Ogre

	return 0;
}

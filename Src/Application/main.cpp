#include <iostream>
#include "GraphicManager.h"
#include "SceneManager.h"

#ifdef _DEBUG 
int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detector de basura
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
#endif
	//Inicializa Ogre y el juego

	GraphicManager * graphicManager = GraphicManager::GetInstance();	//Inicializa Ogre
	graphicManager->InitGraphics();

	SceneManager * sceneManager = SceneManager::GetInstance();			//Inicializa Gestor de escenas
	sceneManager->Go();

	sceneManager->ResetInstance();										//Destruye Gestor de escenas
	graphicManager->ResetInstance();									//Destruye Ogre

	return 0;
}

#include "TutorialApplication.h"
#include "tutorial2.h"


#ifdef _DEBUG || !_WIN32
int main(){
	printf("Hola, Mundo!\n");
	#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){

#endif

	tutorial2 app;
	app.go();
	return 0;
}
/*
#ifdef _DEBUG || !_WIN32

int main(){


#else //_RELEASE

#include <Windows.h> //Hay que incluir la API de windows

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

#endif

	ProyectoBasico * pb = new ProyectoBasico();
	pb->go();
	return 0;
}*/
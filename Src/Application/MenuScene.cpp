#include "MenuScene.h"



using namespace Ogre;

MenuScene::MenuScene() : Scene()
{
}



//M�todo encargado de crear la escena
void MenuScene::CreateScene()
{
	CreateGameObjects();
}

void MenuScene::CreateGameObjects(void)
{
	lectorXML_.Leer("../menu.xml");
}

#include "GameOverScene.h"


using namespace Ogre;

GameOverScene::GameOverScene() : Scene()
{
}


//M�todo encargado de crear la escena
void GameOverScene::CreateScene()
{

	CreateGameObjects();
}

void GameOverScene::CreateGameObjects(void)
{
	lectorXML_.Leer("../gameover.xml");
}
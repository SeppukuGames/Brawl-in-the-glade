#include "MenuScene.h"

//No hace falta, verdad?
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <Box2D.h>


using namespace Ogre;

MenuScene::MenuScene() : Scene()
{
}



//Método encargado de crear la escena
void MenuScene::CreateScene()
{
	//Creamos luz ambiental
	//sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	CreateGameObjects();
}

void MenuScene::CreateGameObjects(void)
{
	lectorXML_.Leer("../../menu.xml");
}

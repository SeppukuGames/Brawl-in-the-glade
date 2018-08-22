#include "Scene1.h"

using namespace Ogre;

Scene1::Scene1() : Scene()
{
}


//M�todo encargado de crear la escena
void Scene1::CreateScene()
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	CreateGameObjects();
}

void Scene1::CreateGameObjects(void)
{
	//TODO: �Se rompe la pausa?
	lectorXML_.Leer("../../escena1.xml"); 
}


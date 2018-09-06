#include "Scene1.h"
#include <iostream>
using namespace Ogre;

Scene1::Scene1() : Scene()
{
}


//Método encargado de crear la escena
void Scene1::CreateScene()
{
	//Creamos luz ambiental
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//std::cout << "Antes de leer xml" << std::endl;
	CreateGameObjects();
	//std::cout << "Después de leer xml" << std::endl;
}

void Scene1::CreateGameObjects(void)
{
	lectorXML_.Leer("../escena1.xml");
	CreateEnemies(2);
}


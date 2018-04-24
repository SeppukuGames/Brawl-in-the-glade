/*
-----------------------------------------------------------------------------
Filename:    tutorial2.cpp
-----------------------------------------------------------------------------
This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

#include "tutorial2.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <time.h>
using namespace Ogre;





//-------------------------------------------------------------------------------------
tutorial2::tutorial2(void)
{
}
//-------------------------------------------------------------------------------------
tutorial2::~tutorial2(void)
{
}

//-------------------------------------------------------------------------------------

void tutorial2::createLights(void)
{
	//Creamos luz ambiental
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//****LUCES****
	//Spotlight
	mSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE); //Ahora el scenemanager usa sombras modulares modulables™

	//Luz para el tutorial 2:
	//LUZ SPOTLIGHT: Foco
	Light* spotlight = mSceneMgr->createLight("SpotLight");
	//Para darle un efecto de PURE BLUE
	spotlight->setDiffuseColour(0, 0, 1.0);
	spotlight->setSpecularColour(0, 0, 1.0);

	spotlight->setType(Light::LT_SPOTLIGHT); //Tipo de luz para el foco (spotlight)

	spotlight->setDirection(Vector3::NEGATIVE_UNIT_Z);		//Dirección de la luz

	SceneNode* spotLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	spotLightNode->attachObject(spotlight);
	spotLightNode->setDirection(-1, -1, 0);
	spotLightNode->setPosition(Vector3(200, 200, 0)); //Posicion de la luz

	spotlight->setSpotlightRange(Degree(35), Degree(50));   //Rango de la luz

	//CON TODO ESTO DE ARRIBA, SALE EL NINJA CON LUZ AZUL

	//LUZ DIRECCIONAL: Luz direcional
	Light* directionalLight = mSceneMgr->createLight("DirectionalLight");

	directionalLight->setType(Light::LT_DIRECTIONAL); //Tipo de luz para la luz direccional

	//IMPORTANTE: La clase Light define un método de SetAttenuagtion que te permite controlar cómo se disipa la luz según se aleja del emisor
	directionalLight->setDiffuseColour(ColourValue(0.4f, 0.0f, 0.0f));
	directionalLight->setSpecularColour(ColourValue(0.4f, 0.0f, 0.0f));


	directionalLight->setDirection(Vector3::NEGATIVE_UNIT_Z);
	SceneNode* directionalLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	directionalLightNode->attachObject(directionalLight);
	directionalLightNode->setDirection(Vector3(0, -1, 1)); //La direccion del nodo

	//LUZ FOCAL: Pues eso
	Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Light::LT_POINT);

	pointLight->setDiffuseColour(Ogre::Real(0.3), Ogre::Real(0.3), Ogre::Real(0.3));
	pointLight->setSpecularColour(Ogre::Real(0.3), Ogre::Real(0.3), Ogre::Real(0.3));

	SceneNode* pointLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pointLightNode->attachObject(pointLight);
	pointLightNode->setPosition(Vector3(0, 150, 250));


	//Para las sombras modulativas
	mSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);


}

//-------------------------------------------------------------------------------------

void tutorial2::createCameras(void)
{
	//Creamos camara
	//LA CÁMARA YA VIENE CREADA POR BASE APPLICATION, SOLO CREAMOS EL NODO
	SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->attachObject(mCamera);
	//cam->setNearClipDistance(5); <- Del Base Application
	camNode->setPosition(200, 300, 400);
	camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);


	/*  VIEWPORT
	Es del Base application pero se hace así:

	Viewport* vp = getRenderWindow()->addViewport(cam);		//Constructora
	vp->setBackgroundColour(ColourValue(0, 0, 0));			//Color del fondo

	cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));	//Aspect ratio (el default)
	*/

}

//-------------------------------------------------------------------------------------

void tutorial2::createEntities(void)
{
	
	//Crear entidades como se hacía en el tutorial 2:

	Entity * ninja = mSceneMgr->createEntity("ninja.mesh");
	SceneNode * ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ninjaNode");
	ninjaNode->attachObject(ninja); //Esto vincula el mesh al nodo de la escena
	
	ninjaNode->setScale(0.5, 0.5, 0.5);
	ninja->setCastShadows(true); //Gracias a esta linea el mesh emite sombras cuando le afecta una luz
	

	//CREAR UN PLANO
	Plane plane(Vector3::UNIT_Y, 0);

	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);

	//Entidad a partir del plano
	Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);							//No queremos que castee sombras
	groundEntity->setMaterialName("Examples/Rockwall");				//El material

	//Crear entidades con COMPONENTES (usa esto)
	/*
	GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);

	//Componentes que se añaden al Game Component
	OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5,5,5)));
	OgritoQueRota->addComponent(new Transform(Ogre::Vector3(1, 0, 0)));
	OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	actors_.push_back(OgritoQueRota);
	*/

	//srand(time(NULL));
	//int random = 0;
	//std::vector<Entity*> entidades_;
	//for (int i = 0; i < 10; i++){
	//	for (int j = 0; j < 10; j++){
	//		random = rand() % 101;
	//		GameComponent * OgritoQueRota = new GameComponent(mSceneMgr);
	//		OgritoQueRota->addComponent(new componenteEscalado(Ogre::Vector3(5, 5, 5)));
	//		OgritoQueRota->addComponent(new Transform(Ogre::Vector3((i * 50) - 300, -20, (j * 50) - 300)));
	//		if (random % 7 == 0)
	//			OgritoQueRota->addComponent(new RenderComponent("arbol.mesh"));
	//		else
	//			OgritoQueRota->addComponent(new RenderComponent("suelo.mesh"));
	//		actors_.push_back(OgritoQueRota);
	//	}
	//}

	//Metodos utiles de la escena:
}

//-------------------------------------------------------------------------------------
void tutorial2::createScene(void)
{
	// create your scene here :)

	
	createLights();

	createCameras();

	createEntities();

}




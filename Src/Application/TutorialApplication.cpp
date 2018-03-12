/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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

#include "TutorialApplication.h"
#include <OgreSceneNode.h>
#include <iostream>

using namespace Ogre;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------

void TutorialApplication::createLights(void)
{
	//Creamos luz ambiental
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//tutorial 2:
	mSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE); //Ahora el scenemanager usa sombras modulares modulables™

	//Luz para el tutorial 2:

	Light* spotlight = mSceneMgr->createLight("SpotLight");
	//Para darle un efecto de PURE BLUE
	spotlight->setDiffuseColour(0, 0, 1.0);
	spotlight->setSpecularColour(0, 0, 1.0);

	spotlight->setType(Light::LT_SPOTLIGHT); //Tipo de luz para el foco (spotlight)

	spotlight->setDirection(Vector3::NEGATIVE_UNIT_Z);		//Dirección de la luz
	spotlight->setSpotlightRange(Degree(35), Degree(50));   //Rango de la luz

	SceneNode* spotLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	spotLightNode->attachObject(spotlight);
	spotLightNode->setDirection(-1, -1, 0);
	spotLightNode->setPosition(Vector3(200, 200, 0)); //Posicion de la luz

	//CON TODO ESTO DE ARRIBA, SALE EL NINJA CON LUZ AZUL

	Light* directionalLight = mSceneMgr->createLight("DirectionalLight");

	//IMPORTANTE: La clase Light define un método de SetAttenuagtion que te permite controlar cómo se disipa la luz según se aleja del emisor
	directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
	directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));

	spotlight->setType(Light::LT_DIRECTIONAL); //Tipo de luz para la luz direccional

	directionalLight->setDirection(Vector3::NEGATIVE_UNIT_Z);
	SceneNode* directionalLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	directionalLightNode->attachObject(directionalLight);
	directionalLightNode->setDirection(Vector3(0, -1, 1)); //La direccion del nodo
		

	Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Light::LT_POINT);

	pointLight->setDiffuseColour(0.3, 0.3, 0.3);
	pointLight->setSpecularColour(0.3, 0.3, 0.3);

	SceneNode* pointLightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pointLightNode->attachObject(pointLight);
	pointLightNode->setPosition(Vector3(0, 150, 250));

	//¿¿¿¿Y LA LUZ ROJA DONDE ESTA????

	//Creamos una luz
	//Ogre tiene tres luces: Point, spotlight, y direccional
	//Light* light = mSceneMgr->createLight("MainLight");
	//SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//lightNode->attachObject(light);
	//
	////Damos posición al nodo de la luz
	//lightNode->setPosition(20, 80, 50);
}

//-------------------------------------------------------------------------------------

void TutorialApplication::createCameras(void)
{
	//Creamos camara
	//LA CÁMARA YA VIENE CREADA POR BASE APPLICATION, SOLO CREAMOS EL NODO
	SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD); //Ejemplo luces y sombras: Mira a un punto concreto
	camNode->attachObject(mCamera);
	camNode->setPosition(0, 47, 222);

	/*
	SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	// create the camera
	Camera* cam = mSceneMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 140);
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	*/
}

//-------------------------------------------------------------------------------------

void TutorialApplication::createEntities(void)
{

	//Creamos entidades. DEBERIAMOS DAR NOMBRES A ENTIDADES Y NODOS
	//Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
	//
	//SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ogreNode->attachObject(ogreEntity);
	//
	//Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
	//SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
	//ogreNode2->attachObject(ogreEntity2);
	//
	////Ogro escalado
	//Entity* ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
	//SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ogreNode3->setPosition(0, 104, 0);
	//ogreNode3->setScale(2, 1.2, 1);
	//ogreNode3->attachObject(ogreEntity3);
	//
	////Ogro rotado
	//Entity* ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
	//SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ogreNode4->setPosition(-84, 48, 0);
	//ogreNode4->roll(Degree(-90));//Puede hacerse en radianes
	//ogreNode4->attachObject(ogreEntity4);

	//TUTORIAL 2: Luces y sombras
	Plane plane(Vector3::UNIT_Y, 0); //CREA UN PLANO EN EL EJE Y
	std::cout << "-------------------------------------------------\nPlano creado.\n";
	// IMPORTANTE: Para la siguiente instrucción, hemos añadido la librería #include <OgreMeshManager.h> en BaseApplication :IMPORTANTE //
	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);
	//
	Entity* entidadSuelo = mSceneMgr->createEntity("ground");
	SceneNode * suelo = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	entidadSuelo->setCastShadows(false);		//No queremos que el suelo genere sombras
	entidadSuelo->setMaterialName("Examples/Rockwall");  //Esto instancia una textura en el suelo.
	suelo->attachObject(entidadSuelo);


	Entity * ninja = mSceneMgr->createEntity("ninja.mesh");
	SceneNode * MariconSaltarin = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	MariconSaltarin ->attachObject(ninja); //Esto vincula el mesh al nodo de la escena
	MariconSaltarin->setScale(0.5, 0.5, 0.5);
	ninja->setCastShadows(true); //Gracias a esta linea el mesh emite sombras cuando le afecta una luz

	//Metodos utiles de la escena:
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();
}



#ifdef _DEBUG || !_WIN32
int main(){
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){

#endif

	TutorialApplication app;
	app.go();
	return 0;
}

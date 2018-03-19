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
	//DECLARACIONES TUTORIAL 5
	mRotate = .13;
	mMove = 250;
	mCamNode = 0;
	mDirection = Ogre::Vector3::ZERO;
	//-----------------------//

}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------

void TutorialApplication::tutorial5(){
	//Tutorial 5
	Entity* tudorEntity = mSceneMgr->createEntity("tudorhouse.mesh"); //La casita :3
	SceneNode * nodoCasa = mSceneMgr->getRootSceneNode()->createChildSceneNode("NodoCASA"); //en el tutorial se llama "node"
	nodoCasa->attachObject(tudorEntity);


	nodoCasa = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(1200, -370, 0));
	nodoCasa->yaw(Ogre::Degree(90));
	
	mCamNode = nodoCasa;
	nodoCasa->attachObject(mCamera);

	nodoCasa = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Ogre::Vector3(-500, -370, 1000));
	nodoCasa->yaw(Ogre::Degree(-30));

}

void TutorialApplication::createLights(void)
{
	//Creamos luz ambiental
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	////////////////////////////////////////////////
	//		TUTORIAL 2: Luces y sombras			///
	///////////////////////////////////////////////
	/*
	mSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE); //Ahora el scenemanager usa sombras modulares modulables™

	//Luz para el tutorial 2:

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

	Light* directionalLight = mSceneMgr->createLight("DirectionalLight");

	directionalLight->setType(Light::LT_DIRECTIONAL); //Tipo de luz para la luz direccional

	//IMPORTANTE: La clase Light define un método de SetAttenuagtion que te permite controlar cómo se disipa la luz según se aleja del emisor
	directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
	directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));
	

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
	*/

	//////////////////////////////////////////////
	//         TUTORIAL 4: Unbuffered input    ///
	//////////////////////////////////////////////

	/*mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));

	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(250, 150, 250);
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);
	*/


	////////////////////////////////////////////////
	//		TUTORIAL 5: Buffered input          ///
	///////////////////////////////////////////////
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .2));

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);


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
	//camNode->setPosition(0, 47, 222);

	
	

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
	///CABEZAS DE OGROS///
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

	////////////////////////////////////////////////
	//		TUTORIAL 2: Luces y sombras			///
	///////////////////////////////////////////////

	//Plane plane(Vector3::UNIT_Y, 0); //CREA UN PLANO EN EL EJE Y
	//std::cout << "-------------------------------------------------\nPlano creado.\n";
	//// IMPORTANTE: Para la siguiente instrucción, hemos añadido la librería #include <OgreMeshManager.h> en BaseApplication :IMPORTANTE //
	//MeshManager::getSingleton().createPlane(
	//	"ground",
	//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//	plane,
	//	1500, 1500, 20, 20,
	//	true,
	//	1, 5, 5,
	//	Vector3::UNIT_Z);
	////
	//Entity* entidadSuelo = mSceneMgr->createEntity("ground");
	//SceneNode * suelo = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//entidadSuelo->setCastShadows(false);		//No queremos que el suelo genere sombras
	//entidadSuelo->setMaterialName("Examples/Rockwall");  //Esto instancia una textura en el suelo.
	//suelo->attachObject(entidadSuelo);

	////NINJA MARICON//
	//Entity * ninja = mSceneMgr->createEntity("ninja.mesh");
	//SceneNode * ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ninjaNode");
	//ninjaNode->attachObject(ninja); //Esto vincula el mesh al nodo de la escena
	//ninjaNode->setScale(0.5, 0.5, 0.5);
	//ninja->setCastShadows(true); //Gracias a esta linea el mesh emite sombras cuando le afecta una luz

	////////////////////////////////////////////////
	//		TUTORIAL 5: Buffered input          ///
	///////////////////////////////////////////////

	Entity* tudorEntity = mSceneMgr->createEntity("tudorhouse.mesh"); //La casita :3
	SceneNode * nodoCasa = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodoCasa"); //en el tutorial se llama "node"
	nodoCasa->attachObject(tudorEntity);




}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// create your scene here :)

	createLights();


	tutorial5();
	//createCameras();

	//createEntities();

	
}

//A saber qué cojones es esto pavo
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	//Esto nos garantia que solo cobtinbuamos si el iput está procesado bien
	if (!processUnbufferedInput(fe))
		return false;

	mCamNode->translate(mDirection * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	bool ret = BaseApplication::frameRenderingQueued(fe);
	
	return ret;
}


bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	//Variables necesarias para el processUnbufferedInput
	static bool mouseDownLastFrame = false; //Static para que se mantenga el valor entre llamadas
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO; //Vector para mantener la direccion del ninja
	static Ogre::Real toggleTimer = 0.0;
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 250;

	/*
	bool leftMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Left);

	if (leftMouseDown && !mouseDownLastFrame)
	{
		Ogre::Light* light = mSceneMgr->getLight("Light1");
		light->setVisible(!light->isVisible());
	}
	//TECLAS DE MOVIMIENTO DEL NINJA//
	if (mKeyboard->isKeyDown(OIS::KC_W)) //Alante
		dirVec.z -= move;

	if (mKeyboard->isKeyDown(OIS::KC_S)) //Atras
		dirVec.z += move;

	if (mKeyboard->isKeyDown(OIS::KC_Q)) //Arriba (eje y)
		dirVec.y += move;

	if (mKeyboard->isKeyDown(OIS::KC_E)) //Abajo (eje y)
		dirVec.y -= move;

	if (mKeyboard->isKeyDown(OIS::KC_A)) //Izq
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("ninjaNode")->yaw(Ogre::Degree(5 * rotate));
		else
			dirVec.x -= move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_D)) //Der
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("ninjaNode")->yaw(Ogre::Degree(-5 * rotate));
		else
			dirVec.x += move;
	}


	//mSceneMgr->getSceneNode("ninjaNode")->translate(
	//	dirVec * fe.timeSinceLastFrame,
	//	Ogre::Node::TS_LOCAL);


	mouseDownLastFrame = leftMouseDown; //Lo asgnamos para asegurarnos que tiene el valor correcto el siguiente frame.
	return true;
	*/
	return true;
}

//Tutorial 5: TECLADO
bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;

	case OIS::KC_1:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
		break;

	case OIS::KC_2:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode2");
		mCamNode->attachObject(mCamera);
		break;

	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = -mMove;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = mMove;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = -mMove;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = mMove;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = -mMove;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = mMove;
		break;

	default:
		break;
	}

	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) 
{ 
	switch (ke.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = 0;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = 0;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = 0;
		break;

	default:
		break;
	}
	return true;
	return true; 
}

//Tutorial 5: RATÓN
bool TutorialApplication::mouseMoved(const OIS::MouseEvent& me)
{
	if (me.state.buttonDown(OIS::MB_Right))
	{
		mCamNode->yaw(Ogre::Degree(-mRotate * me.state.X.rel), Ogre::Node::TS_WORLD);
		mCamNode->pitch(Ogre::Degree(-mRotate * me.state.Y.rel), Ogre::Node::TS_LOCAL);
	}

	return true;
}

bool TutorialApplication::mousePressed(
	const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	switch (id)
	{
	case OIS::MB_Left:
		Ogre::Light* light = mSceneMgr->getLight("Light1");
		light->setVisible(!light->isVisible());
		break;
	}
	return true;
}

bool TutorialApplication::mouseReleased(
	const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
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

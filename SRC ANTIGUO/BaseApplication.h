/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
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
#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OgreRoot.h>
#include <OgreConfigFile.h> //Para parsear los .cfg
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreWindowEventUtilities.h>

//OIS
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreLogManager.h>
#include <OgreMeshManager.h>
//#include <OgreFrameListener.h>
//#include <OgreOverlaySystem.h>
#include <OgreTextureManager.h>

#include "GameObject.h"
#include "Physics.h"
#include "irrKlang.h"

//Overlay
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>

//																									-Listeners de OIS-
class BaseApplication :
	public Ogre::WindowEventListener, //Para OIS, queremos sobreescribir windowResized() y windowClosed()
									  //public Ogre::FrameListener, //Para poder llamar cada frame al input (buffered o no)
	public OIS::KeyListener,
	public OIS::MouseListener
{


	
protected:

	//--------------------------------------ATRIBUTOS-----------------------------------------------

	//Permite inicializar el core de Ogre facilmente
	Ogre::Root *mRoot;

	//Strings que utilizaremos durante el setup
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	//RenderSystem
	Ogre::RenderWindow* mWindow;

	Ogre::SceneManager* mSceneMgr;//Inicializa recursos y rutinas de renderizado
	Ogre::Camera* mCamera;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	//bool mCursorWasVisible;						// was cursor visible before dialog appeared
	
	Ogre::OverlaySystem *mOverlaySystem;//No lo utilizamos?


	//Todos los objetos de las escena
	std::vector<GameObject*> actors_;

	std::vector<OIS::KeyListener*> keyInputObservers;

	std::vector<OIS::MouseListener*> mouseInputObservers;

	Physics * physicsEngine;

	irrklang::ISoundEngine* soundEngine;

	//Para el bucle principal
	double lastTime;
	Ogre::Timer *timer;

	bool pause;

	int numEnemigos = 0;
	int oleadaActual = 1;

	bool gameOver;
	bool mShutDown;
	int playIndex;		//Contador de escenas: Menu principal = 0, MainGame = 1


	//--------------------------------------ATRIBUTOS-----------------------------------------------

public:
	/*
	Ciclo b�sico de Ogre:

	Create the Ogre::Root object
	Define the resources that Ogre will use
	Choose and set up the RenderSystem (DirectX, OpenGL, etc)
	Create the RenderWindow
	Set up any third party libraries and plugins.
	Initialise resources
	Register listener classes
	Build a scene
	Start the render loop

	*/
	BaseApplication(void);
	virtual ~BaseApplication(void);

	virtual void go(void);

	virtual void registerKeyInputObserver(OIS::KeyListener *observer);

	virtual void registerMouseInputObserver(OIS::MouseListener *observer);//�Conflicto?

	virtual Physics * getPhysicsEngine();

	void a�adeGameObject(GameObject * nuevo);

	void quitaGameObject(GameObject * nuevo);

	virtual int getOleada(){ return oleadaActual; }
	virtual int getNumEnemigos() { return numEnemigos; }

protected:	
	virtual bool gameLoop(void);//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame

	virtual bool handleInput(void);//Detecta input
	virtual bool update(double elapsed);
	virtual bool render(void);

	virtual bool setup();
	virtual void setupResources(void);//Establece los recursos potencialmente utilizables. Para a�adir nuevos recursos : resources.cfg
	virtual bool configure(void);//Configura el RenderSystem y crea la ventana
	virtual void loadResources(void);//Carga todos los recursos

	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createViewports(void);

	virtual void initOIS(void);
	virtual void initSoundEngine(void);

	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);

	virtual void NuevaOleada(void) = 0;

	//Overlay
	virtual void initOverlay(void);

	//----------------Window Event Listener---------------

	//Actualiza el estado del rat�n a la nueva ventana
	virtual void windowResized(Ogre::RenderWindow* rw);//Se le llama cada vez que se escala la ventana
													   //Destruye OIS antes de que se cierre la ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);

	//----------------Window Event Listener---------------


	//------------Input Listener----------------------------

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	//------------Input Listener----------------------------
	
};

#endif // #ifndef __BaseApplication_h_
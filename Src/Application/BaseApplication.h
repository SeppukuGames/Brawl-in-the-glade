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

//CEGUI
//#include <CEGUI/CEGUI.h>

#include <OgreLogManager.h>
#include <OgreMeshManager.h>
//#include <OgreFrameListener.h>
//#include <OgreOverlaySystem.h>
#include <OgreTextureManager.h>

#include "GameObject.h"

//																									-Listeners de OIS-
class BaseApplication :
	public Ogre::WindowEventListener //Para OIS, queremos sobreescribir windowResized() y windowClosed()
	//public Ogre::FrameListener, //Para poder llamar cada frame al input (buffered o no)
	//public OIS::KeyListener,
	//public OIS::MouseListener
{
public:
	/*
	Ciclo básico de Ogre:

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

protected:
	virtual bool gameLoop(void);//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame
	
	virtual bool handleInput(void);//Detecta input
	virtual bool update(void);
	virtual bool render(void);

	virtual bool setup();
	virtual void setupResources(void);//Establece los recursos potencialmente utilizables. Para añadir nuevos recursos : resources.cfg
	virtual bool configure(void);//Configura el RenderSystem y crea la ventana
	virtual void loadResources(void);//Carga todos los recursos

	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createViewports(void);

	virtual void initOIS(void);

	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);

	//virtual void createFrameListener(void);
	//virtual void createResourceListener(void);

	//----------------Window Event Listener---------------
	//Actualiza el estado del ratón a la nueva ventana
	virtual void windowResized(Ogre::RenderWindow* rw);//Se le llama cada vez que se escala la ventana
	//Destruye OIS antes de que se cierre la ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);
	//----------------Window Event Listener---------------

	//-----------Frame Listener----------
	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	//-----------Frame Listener----------

	//------------OIS----------------------------
	/*
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	*/
	//------------OIS-----------------------------


	//ATRIBUTOS

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

	/*
	bool mCursorWasVisible;						// was cursor visible before dialog appeared
	bool mShutDown;
	*/
	//Ogre::OverlaySystem *mOverlaySystem;//No lo utilizamos?


	//Todos los objetos de las escena
	std::vector<GameObject*> actors_;


};

#endif // #ifndef __BaseApplication_h_
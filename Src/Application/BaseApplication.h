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

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>
#include <OgreOverlaySystem.h>
#include <OgreTextureManager.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//																									-Listeners de OIS-
class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
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
	virtual bool setup();
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);
	virtual void createViewports(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	//Adjust mouse clipping area
	virtual void windowResized(Ogre::RenderWindow* rw);
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(Ogre::RenderWindow* rw);

	//Permite inicializar el core de Ogre facilmente
	Ogre::Root *mRoot;

	//Strings que utilizaremos durante el setup
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	//RenderSystem
	Ogre::RenderWindow* mWindow;

	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;//Inicializa recursos y rutinas de renderizado

	Ogre::OverlaySystem *mOverlaySystem;

	bool mCursorWasVisible;						// was cursor visible before dialog appeared
	bool mShutDown;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

};

#endif // #ifndef __BaseApplication_h_
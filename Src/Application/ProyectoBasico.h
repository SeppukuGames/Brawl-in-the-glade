#pragma once
#include <stdio.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include <OgreCamera.h>
#include <OgreEntity.h>
#include "OgreSceneNode.h"
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>
#include <OgreWindowEventUtilities.h>
#include <OgreException.h>
#include <string>
#include <iostream>
#include <OgreFrameListener.h>
#include <OgreLogManager.h>
//OIS
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>



class Game: public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	Game();
	virtual ~Game();
	bool go();
	bool loop();
	void close();

private:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::ConfigFile cf;
	Ogre::SceneManager * scnMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::Camera * cam;
	Ogre::Viewport * vp;
	Ogre::Light *light;

	//OISSSSSSSSSSSSSS CUIDAO ALETA
	OIS::InputManager*mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

protected:

	//Métodos que se van a sobrescribir para poder cerrar/eliminar OIS
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow*rw);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};


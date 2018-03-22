/*
-----------------------------------------------------------------------------
Filename:    TutorialBuffered.h
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
#ifndef __TutorialBuffered_h_
#define __TutorialBuffered_h_

#include "BaseApplication.h"

class TutorialBuffered : public BaseApplication
{
public:
	TutorialBuffered(void);
	virtual ~TutorialBuffered(void);

protected:
	virtual void createScene(void);

	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

	virtual bool update(void);

	//------------Input Listener----------------------------

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	//------------Input Listener----------------------------

	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

	Ogre::Real mRotate;
	Ogre::Real mMove;
	Ogre::Vector3 mDirection;
	Ogre::SceneNode* mCamNode;

};

#endif // #ifndef __TutorialBuffered_h_
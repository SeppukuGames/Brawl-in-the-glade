/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	
	//Para el tuto 5 skrr
	Ogre::Real mRotate;
	Ogre::Real mMove;
	Ogre::SceneNode* mCamNode;
	Ogre::Vector3 mDirection;

	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
};

#endif // #ifndef __TutorialApplication_h_
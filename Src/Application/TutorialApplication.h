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
#include "EnemyPrototype.h"
#include "Factory.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameObject.h"


class TutorialApplication : public BaseApplication
{
protected:
	static TutorialApplication * instance;


public:
	TutorialApplication(void);
	//virtual ~TutorialApplication(void);

	static TutorialApplication *getInstance();

protected:

	virtual void createScene(void);
	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

};


#endif // #ifndef __TutorialApplication_h_
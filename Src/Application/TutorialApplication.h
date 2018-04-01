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


class TutorialApplication : public BaseApplication
{
	
	static TutorialApplication * instance;
	TutorialApplication(void);
	//virtual ~TutorialApplication(void);

public:

	static TutorialApplication *getInstance()
	{
		if (!instance)
			instance = new TutorialApplication;
		return instance;
	}

protected:
	virtual void createScene(void);

	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

};


#endif // #ifndef __TutorialApplication_h_
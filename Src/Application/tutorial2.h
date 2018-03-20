/*
-----------------------------------------------------------------------------
Filename:    tutorial2.h
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
#ifndef __tutorial2_h_
#define __tutorial2_h_

#include "BaseApplication.h"

class tutorial2 : public BaseApplication
{
public:
	tutorial2(void);
	virtual ~tutorial2(void);

protected:
	virtual void createScene(void);

	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

};

#endif // #ifndef __tutorial2_h_

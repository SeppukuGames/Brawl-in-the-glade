#ifndef __EscenaMenu_h_
#define __EscenaMenu_h_

#include "BaseApplication.h"
#include "EnemyPrototype.h"
#include "Factory.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameObject.h"

//Overlay
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"

using namespace Ogre;

class EscenaMenu : public BaseApplication
{
	static EscenaMenu * instance;
	EscenaMenu(void);

public:
	static EscenaMenu *getInstance();

protected:
	
	OverlayContainer* Fondo;
	
	Overlay* overlay;

	GameObject * cam;
	SceneNode* camNode;	
	GameObject* boton;

	virtual void createScene(void);
	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);	

};




#endif // #ifndef __EscenaMenu_h_
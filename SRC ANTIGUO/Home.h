#ifndef __HOME_h_
#define __HOME_h_

#include "BaseApplication.h"
#include "EnemyPrototype.h"
#include "Factory.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "GameObject.h"
#include "UICanvas.h"

//Overlay
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

using namespace Ogre;

class Home : public BaseApplication
{

	static Home * instance;

	//virtual ~MainGame(void);

public:

	static Home *getInstance();
	
	Home(void);

	void initGame();
	void quitGame();
	

protected:

	GameObject * cam;
	SceneNode* camNode;

	BillboardSet* billboardSet;
	Billboard* billboard;

	GameObject* menuPrincipal;

	bool partidaTerminada; //para que no podamos dar a pausa durante el menu GameOver

						   //Overlay* overlay;
						   //OverlayContainer* lifeGUI;
						   //GameObject* lifeCanvas;

	virtual void createScene(void);
	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);
	virtual void createGUI(void);
	virtual void NuevaOleada(void) {};
};


#endif // #ifndef __Home_h_
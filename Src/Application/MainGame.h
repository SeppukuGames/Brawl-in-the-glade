/*
-----------------------------------------------------------------------------
Filename:    MainGame.h
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
#ifndef __MAINGAME_h_
#define __MAINGAME_h_

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

class MainGame : public BaseApplication
{

	static MainGame * instance;
	MainGame(void);
	//virtual ~MainGame(void);

public:


	static MainGame *getInstance();

	void setPauseStatus();

	void quitGame();

	bool getGameOverStatus();

	bool getPauseStatus();

	void ShowGameOver();

	void RestartGame();

protected:

	GameObject * cam;
	SceneNode* camNode;
	GameObject* ninja;
	BillboardSet* billboardSet;
	Billboard* billboard;

	GameObject* menuPausa;
	GameObject* menuGO;

	bool partidaTerminada; //para que no podamos dar a pausa durante el menu GameOver
	
	//Overlay* overlay;
	//OverlayContainer* lifeGUI;
	//GameObject* lifeCanvas;

	virtual void createScene(void);
	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);
	virtual void createGUI(void);
};


#endif // #ifndef __MainGame_h_
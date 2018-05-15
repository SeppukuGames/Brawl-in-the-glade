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
#include "buttonGUI.h"

using namespace Ogre;

class EscenaMenu : public BaseApplication
{

	static EscenaMenu * instance;
	EscenaMenu(void);
	//virtual ~TutorialApplication(void);


public:

	static EscenaMenu *getInstance();

protected:

	std::vector<OverlayContainer*> botones;
	OverlayContainer* Fondo;
	int cont = 0;

	void Refrescar(int boton, std::string textoBoton); //le pasamos el index del boton que vamos a alterar
	Overlay* overlay;

	GameObject * cam;
	SceneNode* camNode;	

	virtual void createScene(void);
	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);

};




#endif // #ifndef __EscenaMenu_h_
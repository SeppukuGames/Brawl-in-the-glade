#ifndef CANVASCOMPONENT_H_
#define CANVASCOMPONENT_H_

#include "Component.h"

//Overlay
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
//Overlay
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"


class CanvasComponent : public Component {

private:

	virtual void Start();

	virtual void Update(double elapsed);

	void CanvasComponent::createGUI();

	void CanvasComponent::createHealthBar();

	float maxWidth = 200;
	float maxHeight = 10;
	float YAxis = 250;

public:

	CanvasComponent();

	~CanvasComponent(){
		//El primer paso de GOS a juego de puta madre, luego se rompe ANTES DE LLEGAR A GOS
		//¿Quizá haya algo que no se borra bien en la SEGUNDA VEZ?
		//El error es de tipo abort. Seguir por ahí.
		Ogre::OverlayManager::getSingleton().destroyAllOverlayElements();
		Ogre::OverlayManager::getSingleton().destroyAll();
	};

	void CanvasComponent::setNewUISize(float x, float y);

	float CanvasComponent::getUIWidth();

	float CanvasComponent::getUIHeight();

	void CanvasComponent::HitGameObject(float amount);


protected:
	
	Ogre::OverlayContainer* ovContainer;
	Ogre::Overlay* overlay;
	Ogre::BillboardSet* billboardSet;

};

#endif
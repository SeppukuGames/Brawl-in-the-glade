#ifndef CANVASCOMPONENT_H_
#define CANVASCOMPONENT_H_

#include "Component.h"

//Overlay
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
//Overlay
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"


class CanvasComponent : public Component {

public:

	CanvasComponent(Ogre::OverlayContainer* newContainer, Ogre::Overlay* newOverlay);

	virtual ~CanvasComponent(){};

	virtual void Start() {};

	virtual void Update(double elapsed);

	void CanvasComponent::createGUI();
	
	void CanvasComponent::setNewUISize(float x, float y);

	float CanvasComponent::getUIWidth();

	float CanvasComponent::getUIHeight();


protected:
	Ogre::OverlayContainer* ovContainer;
	Ogre::Overlay* overlay;
};

#endif
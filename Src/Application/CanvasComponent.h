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

public:

	CanvasComponent();

	virtual ~CanvasComponent(){};

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
#ifndef MENUCOMPONENT_H_
#define MENUCOMPONENT_H_

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
//Menu
#include "Boton.h"

class MenuComponent : public Component {

private:

	virtual void Start();

	virtual void Update(double elapsed);

	void MenuComponent::createGUI(std::string imagen);

	std::vector<Boton*>botones_;

	int contador = 0;
	int numBotones = 0;

public:

	MenuComponent(std::string imagen);

	virtual ~MenuComponent(){};

	void MenuComponent::setNewUISize(float x, float y);

	float MenuComponent::getUIWidth();

	float MenuComponent::getUIHeight();

	void MenuComponent::hitGameObject(float amount);

	void MenuComponent::AddButton(Boton* aux);

	int MenuComponent::getNumButtons(){ return numBotones; }


protected:

	Ogre::OverlayContainer* ovContainer;
	Ogre::Overlay* overlay;
	Ogre::BillboardSet* billboardSet;

};

#endif
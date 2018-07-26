#include "CanvasComponent.h"

using namespace Ogre;

CanvasComponent::CanvasComponent(OverlayContainer* newContainer, Overlay* newOverlay) : Component()
{
	ovContainer = newContainer;
	overlay = newOverlay;
}

void CanvasComponent::Update(double elapsed) {
	overlay->show();
};

void CanvasComponent::setNewUISize(float x, float y) {
	ovContainer->setDimensions(x, y);
}

float CanvasComponent::getUIWidth() {
	return ovContainer->getWidth();
}

float CanvasComponent::getUIHeight() {
	return ovContainer->getHeight();
}

void CanvasComponent::createGUI() {

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	//FontManager& fM = FontManager::getSingleton();

	OverlayContainer* lifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "health"));


	lifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	lifeGUI->setPosition(0, 0);
	lifeGUI->setDimensions(300, 35);
	lifeGUI->setMaterialName("health"); 

	OverlayContainer* backLifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "backHealth"));

	backLifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	backLifeGUI->setPosition(0, 0);
	backLifeGUI->setDimensions(300, 35);
	backLifeGUI->setMaterialName("backHealth"); // Optional background material 

	// Create an overlay, and add the panel*/
	Overlay* overlay = overlayManager.create("OverlayPlayer");
	overlay->add2D(backLifeGUI);
	overlay->add2D(lifeGUI);

	//ninja->addComponent(new UICanvas(lifeGUI, overlay));
	//dynamic_cast<PlayerComponent*> (ninja->getComponent(ComponentName::PLAYER))->setPlayerUI();

}
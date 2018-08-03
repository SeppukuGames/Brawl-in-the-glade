#include "CanvasComponent.h"
#include "GameObject.h"
#include "StatsComponent.h"
#include "SceneManager.h"

using namespace Ogre;

const float maxWidth = 200;
const float maxHeight = 10;

CanvasComponent::CanvasComponent() : Component()
{
}

void CanvasComponent::Start() {

	if (gameObject->GetTag() == "Tower")
		createGUI();
	else
		createHealthBar();
};

void CanvasComponent::Update(double elapsed) {

	if (overlay != NULL)
		overlay->show();
};

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
	Overlay* GOoverlay = overlayManager.create("OverlayPlayer");
	GOoverlay->add2D(backLifeGUI);
	GOoverlay->add2D(lifeGUI);

	//ninja->addComponent(new UICanvas(lifeGUI, overlay));
	ovContainer = lifeGUI;
	overlay = GOoverlay;

	//dynamic_cast<PlayerComponent*> (ninja->getComponent(ComponentName::PLAYER))->setPlayerUI();

}

void CanvasComponent::createHealthBar(){
	
	billboardSet = gameObject->GetNode()->getCreator()->createBillboardSet();
	billboardSet->setMaterialName("health");
	billboardSet->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
	billboardSet->setDefaultDimensions(maxWidth, maxHeight);
	Billboard* billboard = billboardSet->createBillboard(Vector3::ZERO);
	billboard->setPosition(Vector3(0, 250, 0));
	gameObject->GetNode()->attachObject(billboardSet);

	ovContainer = NULL;
	overlay = NULL;
}

void CanvasComponent::setNewUISize(float x, float y) {
	ovContainer->setDimensions(x, y);
}

float CanvasComponent::getUIWidth() {
	return ovContainer->getWidth();
}

float CanvasComponent::getUIHeight() {
	return ovContainer->getHeight();
}

void CanvasComponent::HitGameObject(float amount){
	
	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	billboardSet->setDefaultDimensions((maxWidth * stats->GetLife()) / stats->GetMaxLife(), maxHeight);
}

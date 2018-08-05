#include "CanvasComponent.h"
#include "GameObject.h"
#include "StatsComponent.h"
#include "SceneManager.h"
#include "Error.h"

using namespace Ogre;


CanvasComponent::CanvasComponent() : Component()
{
}

void CanvasComponent::Start() {

	if (gameObject->GetTag() == "Tower"){

		maxWidth = 300;
		maxHeight = 30;
		YAxis = 0;

		createGUI();
	}
	else if (gameObject->GetTag() == "Player"){
		
		maxWidth = 150;
		maxHeight = 10;
		YAxis = 250;
		
		createHealthBar();
	}
	else if (gameObject->GetTag() == "Enemy"){

		maxWidth = 100;
		maxHeight = 5;
		YAxis = 150;

		createHealthBar();
	}
	else {
		Error errorE("\n\n\n\n\nERROR (CANVAS): El tag de la entidad no esta definido ");
		throw errorE;
	}
};

void CanvasComponent::Update(double elapsed) {

	if (overlay != NULL)
		overlay->show();
};

void CanvasComponent::createGUI() {

	OverlayManager& overlayManager = OverlayManager::getSingleton();

	OverlayContainer* lifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "health"));


	lifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	lifeGUI->setPosition(0, 0);
	lifeGUI->setDimensions(maxWidth, maxHeight);
	lifeGUI->setMaterialName("health");

	OverlayContainer* backLifeGUI = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "backHealth"));

	backLifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	backLifeGUI->setPosition(0, 0);
	backLifeGUI->setDimensions(maxWidth, maxHeight);
	backLifeGUI->setMaterialName("backHealth"); // Optional background material 

	// Create an overlay, and add the panel*/
	Overlay* GOoverlay = overlayManager.create("OverlayPlayer");
	GOoverlay->add2D(backLifeGUI);
	GOoverlay->add2D(lifeGUI);

	ovContainer = lifeGUI;
	overlay = GOoverlay;

	billboardSet = NULL;

}

void CanvasComponent::createHealthBar(){
	
	billboardSet = gameObject->GetNode()->getCreator()->createBillboardSet();
	billboardSet->setMaterialName("health");
	billboardSet->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
	billboardSet->setDefaultDimensions(maxWidth, maxHeight);
	Billboard* billboard = billboardSet->createBillboard(Vector3::ZERO);
	billboard->setPosition(Vector3(0, YAxis, 0));
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

	if (gameObject->GetTag() == "Tower"){
		setNewUISize((maxWidth * stats->GetLife()) / stats->GetMaxLife(), maxHeight);
	}
	else{		
		billboardSet->setDefaultDimensions((maxWidth * stats->GetLife()) / stats->GetMaxLife(), maxHeight);
	}
}
#include "CanvasComponent.h"
#include "GameObject.h"
#include "StatsComponent.h"
#include "SceneManager.h"
#include "Error.h"




CanvasComponent::CanvasComponent() : Component()
{
}

CanvasComponent::~CanvasComponent(){
	
	if (gameObject->GetTag() == "Tower"){
		Ogre::OverlayManager::getSingleton().destroyAllOverlayElements();
		Ogre::OverlayManager::getSingleton().destroyAll();
	}
		
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

		maxWidth = 60;
		maxHeight = 3;
		YAxis = 80;

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

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	Ogre::OverlayContainer* lifeGUI = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "health"));

	lifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	lifeGUI->setPosition(0, 0);
	lifeGUI->setDimensions(maxWidth, maxHeight);
	lifeGUI->setMaterialName("health");

	Ogre::OverlayContainer* backLifeGUI = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "backHealth"));

	backLifeGUI->setMetricsMode(Ogre::GMM_PIXELS);
	backLifeGUI->setPosition(0, 0);
	backLifeGUI->setDimensions(maxWidth, maxHeight);
	backLifeGUI->setMaterialName("backHealth"); // Optional background material 

	// Create an overlay, and add the panel*/
	Ogre::Overlay* GOoverlay = overlayManager.create("OverlayPlayer");
	GOoverlay->add2D(backLifeGUI);
	GOoverlay->add2D(lifeGUI);

	ovContainer = lifeGUI;
	overlay = GOoverlay;

	billboardSet = NULL;

}

void CanvasComponent::createHealthBar(){
	
	billboardSet = gameObject->GetNode()->getCreator()->createBillboardSet();
	billboardSet->setMaterialName("health");
	billboardSet->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
	billboardSet->setDefaultDimensions(maxWidth, maxHeight);
	Ogre::Billboard* billboard = billboardSet->createBillboard(Ogre::Vector3::ZERO);
	billboard->setPosition(Ogre::Vector3(0, YAxis, 0));
	gameObject->GetNode()->attachObject(billboardSet);

	ovContainer = NULL;
	overlay = NULL;
}

void CanvasComponent::setNewUISize(float x, float y) {
	if (ovContainer == nullptr) createGUI();
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

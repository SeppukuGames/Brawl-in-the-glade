#include "MenuComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "StatsComponent.h"
#include "InputManager.h"



const float maxWidth = 1200;
const float maxHeight = 500;

MenuComponent::MenuComponent(std::string imagen) : Component()
{
	createGUI(imagen);
}

//Destructora que se encarga de borrar la imagen del GUI y los botones
MenuComponent::~MenuComponent(){

		Ogre::OverlayManager::getSingleton().destroyAllOverlayElements();

		Ogre::OverlayManager::getSingleton().destroyAll();

		if (SceneManager::GetInstance()->getIsPaused()){
		//llama a la torre para que restituya la vida
			
		}
	
}


void MenuComponent::Start() 
{
		
};

void MenuComponent::Update(double elapsed) {

	if (overlay != NULL)
	{
		overlay->show();
		for (int i = 0; i < botones_.size(); i++){
			botones_[i]->getOverlay()->show();
			botones_[i]->Apagar();
		}

		//INPUT
		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_W) || Input::GetInstance()->getKey(OIS::KeyCode::KC_UP))
		{
			if (contador > 0)
				contador--;
		}

		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_S) || Input::GetInstance()->getKey(OIS::KeyCode::KC_DOWN))
		{
			if (contador < botones_.size() - 1)
				contador++;
		}
		
		//Para que el contador no se salga de rango
		if (contador < 0) contador = 0;
		if (contador > botones_.size() - 1) contador = botones_.size() - 1;

		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_RETURN)){
			if (botones_[contador])
				botones_[contador]->Action();
		}

		//Iluminar boton activo
		if (botones_[contador])
			botones_[contador]->Iluminar();
	}	
};

void MenuComponent::createGUI(std::string imagen) {

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	
	Ogre::OverlayContainer* menuGUI = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "ImagenMenu"));

	menuGUI->setMetricsMode(Ogre::GMM_PIXELS);
	menuGUI->setPosition(80, 0);
	menuGUI->setDimensions(850, 400);
	menuGUI->setMaterialName(imagen);

	// Create an overlay, and add the panel*/
	Ogre::Overlay* GOoverlay = overlayManager.create("OverlayMenu");
	
	GOoverlay->add2D(menuGUI);

	ovContainer = menuGUI;
	overlay = GOoverlay;
}

void MenuComponent::setNewUISize(float x, float y) {
	ovContainer->setDimensions(x, y);
}

float MenuComponent::getUIWidth() {
	return ovContainer->getWidth();
}

float MenuComponent::getUIHeight() {
	return ovContainer->getHeight();
}

void MenuComponent::hitGameObject(float amount){
	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	stats->HitGameObject(amount);
	billboardSet->setDefaultDimensions((maxWidth * stats->GetLife()) / stats->GetMaxLife(), maxHeight);
}

void MenuComponent::AddButton(Boton* aux)
{
	botones_.push_back(aux);
	aux->setPosition(450, 450 + (50 * numBotones));	
	numBotones++;
}

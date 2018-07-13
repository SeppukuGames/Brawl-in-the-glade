#ifndef PANELOLEADA_H_
#define PANELOLEADA_H_

#include "Component.h"
#include "KeyInputComponent.h"
#include "GameObject.h"
#include <iostream>

//Overlay
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"

enum panelType { OLEADA, NUM_ENEMIGOS};

class PanelOleada : public KeyInputComponent, public Component {
public:

	PanelOleada(panelType type) : KeyInputComponent(1), Component()
	{
		_type = type;
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "PanelOleada" + std::to_string(_type)));

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		
		switch (_type) {
		case OLEADA:
			panel->setPosition(20, 50);
			break;
		case NUM_ENEMIGOS:
			panel->setPosition(20, 110);
			break;
		}
		
		panel->setDimensions(150, 40);
		panel->setMaterialName("panel2"); // Optional background material 

		//texto		
		textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaPanel" + std::to_string(_type)));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 0);
		textArea->setDimensions(100, 100);
		textArea->setCaption("Fleje bonito");
		textArea->setCharHeight(50);
		textArea->setFontName("Trebuchet");
		textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));

		textArea->setColourTop(ColourValue(1.0, 1.0, 1.0));	
		// Add the text area to the panel		
		panel->addChild(textArea);
		// Create an overlay, and add the panel*/
		overlay = overlayManager.create("PanelOleadas" + std::to_string(_type));
		overlay->add2D(panel);		
		// Show the overlay*/
		overlay->show();

	};

	virtual ~PanelOleada(){};

	virtual void start(){

	};

	virtual void tick(double elapsed)
	{
		switch (_type) {
		case OLEADA:
			textArea->setCaption("Oleada: " + std::to_string(baseGame->getOleada()));
			break;
		case NUM_ENEMIGOS:
			textArea->setCaption("Enemigos: " + std::to_string(baseGame->getNumEnemigos()));
			break;
		default:
			textArea->setCaption("Enemigos: " + std::to_string(baseGame->getNumEnemigos()));
			break;
		}
		

		if (show)
			overlay->show();
		else
			overlay->hide();
	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){
		return true;
	}

	void Show()	{
		show = true;
	}

	void Hide(){
		show = false;
	}

	void SetMainGameRef(MainGame* game) {

		baseGame = game;
	}

private:
	OverlayContainer* panel;
	TextAreaOverlayElement* textArea;

	MainGame* baseGame;
	bool show = true;
	Overlay* overlay;
	panelType _type;
};

#endif /* MENUGAMEOVER_H_ */
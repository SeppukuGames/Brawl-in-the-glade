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

class PanelOleada : public KeyInputComponent, public Component {
public:

	PanelOleada() : KeyInputComponent(1), Component()
	{
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "PanelOleada"));

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(20, 50);

		panel->setDimensions(150, 40);
		panel->setMaterialName("panel2"); // Optional background material 

		//texto		
		textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaPanel"));
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
		overlay = overlayManager.create("PanelOleadas");		
		overlay->add2D(panel);		

		// Show the overlay*/
		overlay->show();

	};

	virtual ~PanelOleada(){};

	virtual void start(){

	};

	virtual void tick(double elapsed)
	{
		textArea->setCaption("Oleada: " + std::to_string(baseGame->getOleada()));

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
};

#endif /* MENUGAMEOVER_H_ */
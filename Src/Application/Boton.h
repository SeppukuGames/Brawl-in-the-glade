#ifndef BOTON_H_
#define BOTON_H_

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

class Boton : public KeyInputComponent, public Component {
public:

	Boton() : KeyInputComponent(), Component()
	{
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		// Create a panel
		for (int i = 1; i <= 3; i++){
			OverlayContainer* panel = static_cast<OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "panel" + std::to_string(i)));

			panel->setMetricsMode(Ogre::GMM_PIXELS);
			panel->setPosition(450, 450 + (50 * i));
			panel->setDimensions(0, 0);
			panel->setMaterialName("panel"); // Optional background material 

			//texto		
			TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
				overlayManager.createOverlayElement("TextArea", "TextAreaName" + std::to_string(i)));
			textArea->setMetricsMode(Ogre::GMM_PIXELS);
			textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
			textArea->setPosition(70, 50);
			textArea->setDimensions(100, 100);
			switch (i)
			{
			case 1:
				textArea->setCaption("Comenzar partida");
				break;
			case 2:
				textArea->setCaption("Controles");
				break;
			case 3:
				textArea->setCaption("Salir");
				break;
			default:
				break;
			}

			textArea->setCharHeight(50);
			textArea->setFontName("Trebuchet");
			textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));
			textArea->setColourTop(ColourValue(1.0, 1.0, 1.0));

			// Add the text area to the panel		
			panel->addChild(textArea);

			botones.push_back(panel);
		}

		// Create an overlay, and add the panel*/
		overlay = overlayManager.create("OverlayNameAux");
		for (int i = 0; i < botones.size(); i++){
			overlay->add2D(botones[i]);
		}

		// Show the overlay*/
		overlay->show();
	};

	virtual ~Boton(){};

	virtual void start(){
		cont = 0;
	};

	virtual void tick(double elapsed){

	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){

		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			switch (cont)
			{
			

			default:
				break;
			}
			
			
			//actualizarBoton() // que llama a refrescar dos veces
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:			
		case 0:
		case 1:
			cont++;
			Refrescar(cont, "string", true);
			Refrescar(cont - 1, "String", false);
			break;

		case OIS::KC_SPACE: //ejecutar
			switch (cont)
			{
			case 0:
			case 1:
			case 2:

				std::cout << "mu bien!has pulsao el boton" << cont << std::endl;
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}

		return true;
	};
	
	

	//le pasamos el index del boton que vamos a alterar
	void Refrescar(int boton, std::string textoBoton, bool azul)
	{
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		delete botones[boton];
		overlay = nullptr;

		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "panel" + std::to_string(cont)));

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(450, 450 + (50 * (boton + 1)));
		panel->setDimensions(0, 0);
		panel->setMaterialName("panel"); // Optional background material 

		//texto		
		TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaName"));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 50);
		textArea->setDimensions(100, 100);
		textArea->setCaption(textoBoton);

		textArea->setCharHeight(50);
		textArea->setFontName("Trebuchet");

		if (azul)
			textArea->setColourBottom(ColourValue(0.0, 0.0, 1.0));
		else
			textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));

		textArea->setColourTop(ColourValue(0.0, 1.0, 1.0));

		// Add the text area to the panel		
		panel->addChild(textArea);
		botones[boton] = panel;

		// Refrescar overlay*/
		overlay = overlayManager.create("OverlayName" + std::to_string(cont));
		for (int i = 0; i < botones.size(); i++){
			overlay->add2D(botones[i]);
		}

		// Show the overlay*/
		overlay->show();
	}

	int cont = 0;

private:
	std::vector<OverlayContainer*> botones;

	Overlay* overlay;
};

#endif /* BOTON_H_ */
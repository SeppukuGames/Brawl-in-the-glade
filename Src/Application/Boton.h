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
		for (int i = 0; i < 3; i++){
			OverlayContainer* panel = static_cast<OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "menu" + std::to_string(i)));

			nombres.push_back(panel->getName()); //Para acceder posteriormente

			std::cout << nombres[i] << std::endl;

			panel->setMetricsMode(Ogre::GMM_PIXELS);
			panel->setPosition(450, 450 + (50 * i));
			panel->setDimensions(0, 0);
			panel->setMaterialName("panel"); // Optional background material 						

			posiciones.push_back(450 + (50*i));

			//texto		
			TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
				overlayManager.createOverlayElement("TextArea", "TextAreaName" + std::to_string(i)));
			textArea->setMetricsMode(Ogre::GMM_PIXELS);
			textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
			textArea->setPosition(70, 50);
			textArea->setDimensions(100, 100);
			nombres2.push_back(textArea->getName());

			switch (i)
			{
			case 0:
				textArea->setCaption("Comenzar partida");
				break;
			case 1:
				textArea->setCaption("Controles");
				break;
			case 2:
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
		overlay = overlayManager.create("OverlayManager");
		for (int i = 0; i < botones.size(); i++){
			overlay->add2D(botones[i]);
		}

		// Show the overlay*/
		overlay->show();
		Refrescar(0, "Comenzar partida", true);
		cont = 0;
	};

	virtual ~Boton(){};

	virtual void start(){
		
	};

	virtual void tick(double elapsed){
		if (cont > 2)
			cont = 2;

		if (cont < 0)
			cont = 0;
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
			case 1:
				Refrescar(1, "Controles", false);
				Refrescar(0, "Comenzar partida", true);
				break;

			case 2:
				Refrescar(2, "Salir", false);
				Refrescar(1, "Controles", true);
				break;
			}
			cont--;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:		
			
			switch (cont)
			{
			case 0:
				Refrescar(1, "Controles", true);
				Refrescar(0, "Comenzar partida", false);
				break;
				
			case 1:
				Refrescar(2, "Salir", true);
				Refrescar(1, "Controles", false);
				break;
			}
			cont++;
			break;
		

		case OIS::KC_SPACE: //ejecutar
			switch (cont)
			{
			case 0:
			case 1:
			case 2:

				std::cout << "mu bien!has pulsao el boton " << cont << std::endl;
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
		
		overlayManager.destroyOverlayElement(nombres[boton]); //panel
		overlayManager.destroyOverlayElement(nombres2[boton]); //textArea
		
		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", nombres[boton])); //creamos elemento de nuevo

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(450, 450 + (50 * (boton)));
		panel->setDimensions(0, 0);
		panel->setMaterialName("panel"); // Optional background material 

		//texto		
		TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", nombres2[boton]));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 50);
		textArea->setDimensions(100, 100);
		textArea->setCaption(textoBoton);

		textArea->setCharHeight(50);
		textArea->setFontName("Trebuchet");

		if (azul)
			textArea->setColourBottom(ColourValue(0.0, 0.0, 0.8));
		else
			textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));

		textArea->setColourTop(ColourValue(1.0, 1.0, 1.0));

		// Add the text area to the panel		
		panel->addChild(textArea);
		botones[boton] = panel;

		// Refrescar overlay*/

		overlay->remove2D(botones[boton]);

		overlay->add2D(botones[boton]);

		// Show the overlay*/
		overlay->show();
	}

	int cont = 0;

private:
	std::vector<OverlayContainer*> botones;
	std::vector<std::string> nombres;
	std::vector<std::string> nombres2;

	std::vector<int> posiciones;	

	Overlay* overlay;
};

#endif /* BOTON_H_ */
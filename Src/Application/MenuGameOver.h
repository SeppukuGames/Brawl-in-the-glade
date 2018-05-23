#ifndef MENUGAMEOVER_H_
#define MENUGAMEOVER_H_

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

class MenuGameOver : public KeyInputComponent, public Component {
public:

	MenuGameOver() : KeyInputComponent(), Component()
	{
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		// Create a panel
		for (int i = 0; i < 3; i++){
			OverlayContainer* panel = static_cast<OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "menuGO" + std::to_string(i)));

			nombres.push_back(panel->getName()); //Para acceder posteriormente			

			panel->setMetricsMode(Ogre::GMM_PIXELS);
			if (i == 2)
				panel->setPosition(450, 450 + (50 * 4));
			else
				panel->setPosition(450, 250 + (50 * i));

			panel->setDimensions(0, 0);
			panel->setMaterialName("panel"); // Optional background material 						

			posiciones.push_back(450 + (50 * i));

			//texto		
			TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
				overlayManager.createOverlayElement("TextArea", "TextAreaNameGO" + std::to_string(i)));
			textArea->setMetricsMode(Ogre::GMM_PIXELS);
			textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
			textArea->setPosition(70, 50);
			textArea->setDimensions(100, 100);
			nombresText.push_back(textArea->getName());

			switch (i)
			{
			case 0:
				textArea->setCaption("Reintentar");
				textoBoton.push_back("Reintentar");
				break;
			case 1:
				textArea->setCaption("Salir");
				textoBoton.push_back("Salir");
				break;
			case 2:
				textArea->setCaption("WS para desplazarse y SPACE para aceptar");
				break;			
			default:
				break;
			}
			if (i == 3)
				textArea->setCharHeight(30);
			else
				textArea->setCharHeight(50);

			textArea->setFontName("Trebuchet");
			if (i == 3)
				textArea->setColourBottom(ColourValue(1.0, 1.0, 1.0));
			else
				textArea->setColourBottom(ColourValue(0.0, 0.0, 0.0));

			textArea->setColourTop(ColourValue(1.0, 1.0, 1.0));

			// Add the text area to the panel		
			panel->addChild(textArea);

			botones.push_back(panel);
		}

		//Fondo
		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "fonditoGO"));

		nombres.push_back(panel->getName()); //Para acceder posteriormente			

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(0, 0);
		panel->setDimensions(1030, 930);
		panel->setMaterialName("panel2"); // Optional background material 						

		botones.push_back(panel);		

		//Fondo
		OverlayContainer* fondoGO = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "fonditoDIED"));

		nombres.push_back(fondoGO->getName()); //Para acceder posteriormente			

		fondoGO->setMetricsMode(Ogre::GMM_PIXELS);
		fondoGO->setPosition(70, 100);
		fondoGO->setDimensions(930, 470);
		fondoGO->setMaterialName("game_over"); // Optional background material 						

		botones.push_back(fondoGO);

		// Create an overlay, and add the panel*/
		overlay = overlayManager.create("OverlayManagerGO");
		for (int i = 0; i < botones.size(); i++){
			overlay->add2D(botones[i]);
		}

		// Show the overlay*/
		//overlay->show();
		Refrescar(0, true);
		Refrescar(1, false);			
		cont = 0;
	};

	virtual ~MenuGameOver(){};

	virtual void start(){

	};
	
	virtual void tick(double elapsed){
		if (cont > 1)
			cont = 1;

		if (cont < 0)
			cont = 0;

		if (show)
			overlay->show();
		else
			overlay->hide();
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
				if (show){
					Refrescar(cont, false);
					Refrescar(cont - 1, true);
					cont--;
				}
				break;
			}
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:

			switch (cont)
			{
			case 0:		
				if (show){
					Refrescar(cont + 1, true);
					Refrescar(cont, false);
					cont++;
				}
				break;
			}
			break;

		case OIS::KC_SPACE: //ejecutar
			switch (cont)
			{
			case 0:
				//baseGame->NuevaPartida();
				if (show)
					std::cout << "Boton " << cont << std::endl;
				break;
			case 1:	
				if (show)
					baseGame->quitGame();
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
	void Refrescar(int boton, bool azul)
	{
		OverlayManager& overlayManager = OverlayManager::getSingleton();
		FontManager& fM = FontManager::getSingleton();

		overlayManager.destroyOverlayElement(nombres[boton]); //panel
		overlayManager.destroyOverlayElement(nombresText[boton]); //textArea

		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", nombres[boton])); //creamos elemento de nuevo

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(450, 450 + (50 * (boton)));
		panel->setDimensions(0, 0);
		panel->setMaterialName("panel"); // Optional background material 

		//texto		
		TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", nombresText[boton]));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 50);
		textArea->setDimensions(100, 100);
		textArea->setCaption(textoBoton[boton]);

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
		
	void ShowMenu()	{	
		show = true;			
	}

	void HideMenu(){ 
		show = false;
	}

	void SetMainGameRef(MainGame* game) {

		baseGame = game;
	}

private:
	std::vector<OverlayContainer*> botones;
	std::vector<std::string> nombres;
	std::vector<std::string> nombresText;
	std::vector<std::string> textoBoton;

	std::vector<int> posiciones;
	int cont = 0;
	MainGame* baseGame;		

	bool show = false;

	Overlay* overlay;
};

#endif /* MENUGAMEOVER_H_ */
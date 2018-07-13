#include "MenuPrincipal.h"
#include "MenuPausa.h"
#include "KeyInputComponent.h"

using namespace Ogre;

MenuPrincipal::MenuPrincipal() : KeyInputComponent(0), Component()
{
	MenuPrincipal::setMenu();
	
}

void MenuPrincipal::start() {

};

void MenuPrincipal::tick(double elapsed) {
	if (cont > 2)
		cont = 2;

	if (cont < 0)
		cont = 0;
};

bool MenuPrincipal::keyPressed(const OIS::KeyEvent &arg) {
	return true;
};

bool MenuPrincipal::keyReleased(const OIS::KeyEvent &arg) {

	switch (arg.key)
	{

	case OIS::KC_UP:
	case OIS::KC_W:
		switch (cont)
		{
		case 1:
		case 2:
			if (show) {
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
		case 1:
			if (show) {
				Refrescar(cont + 1, true);
				Refrescar(cont, false);
				cont++;
			}
			break;
		}
		break;

	case OIS::KC_SPACE: //ejecutar
		if (show) {
			switch (cont)
			{
			case 0:
				Show(false);
				game->initGame();
				break;
			case 1:
				ShowControles();
				break;
			case 2:
				game->quitGame();
				break;

			default:
				break;
			}
		}
		break;

	case OIS::KC_P:
			//show = !show;
			//Show(show);
		break;

	default:
		break;
	}

	return true;
};

//le pasamos el index del boton que vamos a alterar
void MenuPrincipal::Refrescar(int boton, bool azul)
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

void MenuPrincipal::Show(bool aux)
{
	show = aux;
	if (show)
	{
		for (int i = 0; i < botones.size() - 1; i++)
			overlay->add2D(botones[i]);

		Refrescar(0, true);
		Refrescar(1, false);
		Refrescar(2, false);
		cont = 0;

	}
	else
	{
		for (int i = 0; i < botones.size(); i++)
			overlay->remove2D(botones[i]);
	}
}

void MenuPrincipal::ShowControles()
{
	showControl = !showControl;

	if (showControl) {
		for (int i = 0; i < botones.size() - 1; i++)
			overlay->remove2D(botones[i]);
		overlay->add2D(botones[6]);
	}
	else {
		overlay->remove2D(botones[6]);
		for (int i = 0; i < botones.size() - 1; i++)
			overlay->add2D(botones[i]);

		Refrescar(0, false);
		Refrescar(1, true);
		Refrescar(2, false);
		cont = 1;
	}
}

void MenuPrincipal::SetMainGameRef(Home* mainGame) {

	game = mainGame;
}


void MenuPrincipal::setMenu() {

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	FontManager& fM = FontManager::getSingleton();
	// Create a panel
	for (int i = 0; i < 4; i++) {
		OverlayContainer* panel = static_cast<OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "menu" + std::to_string(i)));

		nombres.push_back(panel->getName()); //Para acceder posteriormente			

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		if (i == 3)
			panel->setPosition(450, 450 + (50 * 4));
		else
			panel->setPosition(450, 450 + (50 * i));

		panel->setDimensions(0, 0);
		panel->setMaterialName("panel"); // Optional background material 						

		posiciones.push_back(450 + (50 * i));

		//texto		
		TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaName" + std::to_string(i)));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
		textArea->setPosition(70, 50);
		textArea->setDimensions(100, 100);
		nombresText.push_back(textArea->getName());

		switch (i)
		{
		case 0:
			textArea->setCaption("Comenzar partida");
			textoBoton.push_back("Comenzar partida");
			break;
		case 1:
			textArea->setCaption("Controles");
			textoBoton.push_back("Controles");
			break;
		case 2:
			textArea->setCaption("Salir");
			textoBoton.push_back("Salir");
			break;
		case 3:
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

	//BackGround
	OverlayContainer* panel = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "fondito"));

	nombres.push_back(panel->getName()); //Para acceder posteriormente			

	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(70, 470);
	panel->setDimensions(900, 200);
	panel->setMaterialName("panel2"); // Optional background material 						

	botones.push_back(panel);

	//Fondo Inicio
	OverlayContainer* fondoGO = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "Fondo"));

	nombres.push_back(fondoGO->getName()); //Para acceder posteriormente			

	fondoGO->setMetricsMode(Ogre::GMM_PIXELS);
	fondoGO->setPosition(270, 50);
	fondoGO->setDimensions(500, 300);
	fondoGO->setMaterialName("Fondo"); // Optional background material 						

	botones.push_back(fondoGO);

	//Panel de controles
	OverlayContainer* controles = static_cast<OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "controles"));

	nombres.push_back(controles->getName()); //Para acceder posteriormente			

	controles->setMetricsMode(Ogre::GMM_PIXELS);
	controles->setPosition(70, 120);
	controles->setDimensions(900, 470);
	controles->setMaterialName("controles"); // Optional background material 						

	botones.push_back(controles);

	// Create an overlay, and add the panel*/
	overlay = overlayManager.create("OverlayManager");
	for (int i = 0; i < botones.size(); i++) {
		overlay->add2D(botones[i]);
	}

	overlay->remove2D(botones[6]);
	// Show the overlay*/	
	overlay->show();
	Refrescar(0, true);
	Refrescar(1, false);
	Refrescar(2, false);
	show = true;
	cont = 0;
}
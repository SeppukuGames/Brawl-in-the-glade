#ifndef MENUPRINCIPAL_H_
#define MENUPRINCIPAL_H_


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

class MenuPrincipal : public KeyInputComponent, public Component  {
	
public:

	MenuPrincipal();
	virtual ~MenuPrincipal() {};

	virtual void start();
	virtual void tick(double elapsed);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	void Refrescar(int boton, bool azul);
	void Show(bool aux);
	void ShowControles();
	void SetMainGameRef(Home* mainGame);

	void setMenu();

	protected:
		std::vector<OverlayContainer*> botones;
		std::vector<std::string> nombres;
		std::vector<std::string> nombresText;
		std::vector<std::string> textoBoton;

		std::vector<int> posiciones;

		Overlay* overlay;
		Home* game;
		int cont = 0;
		bool show = false;
		bool showControl = false;

};



#endif /* MENUPRINCIPAL_H_ */
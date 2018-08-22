#ifndef BOTON_H_
#define BOTON_H_

#include "Component.h"

//Overlay
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
//Overlay
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreBorderPanelOverlayElement.h"

enum ButtonType{
	START, OPTIONS, BUTTONEXIT
};

class Boton : public Component {

private:

	virtual void Start();

	virtual void Update(double elapsed);

	void Boton::createButton(std::string texto, int n);

	ButtonType tipo = START;

	std::string nombreBoton;	//Almacena el nombre del overlaycontainer
	std::string nombreTexto;	//Almacena el nombre del textArea

public:

	Boton(std::string texto, int n);

	~Boton();

	void Boton::setNewUISize(float x, float y);

	float Boton::getUIWidth();

	float Boton::getUIHeight();

	void Boton::hitGameObject(float amount);

	Ogre::Overlay* Boton::getOverlay(){ return overlay; }

	void Boton::setPosition(int n, int n2);

	void Boton::Iluminar();										//Colorear de azul el botón
	
	void Boton::Apagar();										//Colorear de blanco el botón

	void Boton::Action();										//Según el tipo de botón, realizará una acción determinada

	void Boton::setAction(std::string accion);					//Define qué tipo de boton es

protected:

	Ogre::OverlayContainer* ovContainer;
	Ogre::Overlay* overlay;
	Ogre::BillboardSet* billboardSet;

};

#endif
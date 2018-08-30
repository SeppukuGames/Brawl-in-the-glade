#include "Boton.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "StatsComponent.h"


const float maxWidth = 200;
const float maxHeight = 35;

Boton::Boton(std::string texto, int n) : Component()
{
	createButton(texto, n);
}

//Destruye la imagen asociada al botón
Boton::~Boton(){
	//delete ovContainer;
	Ogre::OverlayManager::getSingleton().destroyAllOverlayElements();
	Ogre::OverlayManager::getSingleton().destroyAll();

}

void Boton::Start()
{
};

void Boton::Update(double elapsed)
{
};

void Boton::createButton(std::string texto, int n) {

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	//FontManager& fM = FontManager::getSingleton();

	nombreBoton = texto;

	Ogre::OverlayContainer* button = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", nombreBoton));

	button->setMetricsMode(Ogre::GMM_PIXELS);
	button->setPosition(350, 450);
	button->setDimensions(0, 0);
	button->setMaterialName("Fondo");

	nombreTexto = texto + std::to_string(n);

	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea", nombreTexto));

	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
	textArea->setPosition(70, 50);
	textArea->setDimensions(100, 100);
	textArea->setCaption(texto);

	textArea->setCharHeight(50);
	textArea->setFontName("Trebuchet");
		
	textArea->setColourBottom(Ogre::ColourValue(0.0, 0.0, 0.0));
	textArea->setColourTop(Ogre::ColourValue(1.0, 1.0, 1.0));

	// Add the text area to the panel
	button->addChild(textArea);

	// Create an overlay, and add the panel*/
	Ogre::Overlay* GOoverlay = overlayManager.create(texto);

	GOoverlay->add2D(button);

	ovContainer = button;
	overlay = GOoverlay;
}

void Boton::setNewUISize(float x, float y) {
	ovContainer->setDimensions(x, y);
}

float Boton::getUIWidth() {
	return ovContainer->getWidth();
}

float Boton::getUIHeight() {
	return ovContainer->getHeight();
}

void Boton::hitGameObject(float amount){
	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	stats->HitGameObject(amount);
	billboardSet->setDefaultDimensions((maxWidth * stats->GetLife()) / stats->GetMaxLife(), maxHeight);
}

void Boton::setPosition(int n, int n2)
{
	if (overlay->getChild(nombreBoton))
		overlay->getChild(nombreBoton)->setPosition(n, n2);
}

void Boton::Iluminar()
{
	ovContainer->getChild(nombreTexto);

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager.getOverlayElement(nombreTexto));

	textArea->setColourBottom(Ogre::ColourValue(0.0, 0.0, 0.8));
}

void Boton::Apagar()
{
	ovContainer->getChild(nombreTexto);

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager.getOverlayElement(nombreTexto));

	textArea->setColourBottom(Ogre::ColourValue(0.0, 0.0, 0.0));
}

void Boton::setAction(std::string accion)
{
	if (accion == "Start")
		tipo = ButtonType::START;
	if (accion == "Resume")
		tipo = ButtonType::RESUME;
	if (accion == "Options")
		tipo = ButtonType::OPTIONS;
	if (accion == "Exit")
		tipo = ButtonType::BUTTONEXIT;
}

void Boton::Action()
{
	switch (tipo)
	{
	case START:
		std::cout << "Soy start" << std::endl;
		SceneManager::GetInstance()->LoadScene(SCENE1);
		break;
	case OPTIONS:
		std::cout << "Soy opciones" << std::endl;
		break;
	case RESUME:
		SceneManager::GetInstance()->UnloadPauseScene();
		std::cout << "Soy una decepción" << std::endl;
		break;
	case BUTTONEXIT:
		std::cout << "Soy exit" << std::endl;
		break;
	default:
		break;
	}
}
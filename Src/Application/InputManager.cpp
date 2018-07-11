#include "InputManager.h"
#include "GraphicManager.h"

#include <OgreRenderWindow.h>
#include <OgreLogManager.h>



#pragma region Singleton  
/* Null, because instance will be initialized on demand. */
Input* Input::instance = 0;

Input* Input::GetInstance()
{
	if (instance == 0)
		instance = new Input();

	return instance;
}

void Input::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

Input::Input() :
keys(NUMKEYS, false),
keysMouse(NUMKEYMOUSE, false),
inputManager(0),
mouse(0),
keyboard(0)
{}

Input::~Input(){
	Ogre::WindowEventUtilities::removeWindowEventListener(GraphicManager::GetInstance()->GetWindow(), this);
	windowClosed(GraphicManager::GetInstance()->GetWindow());
}

void Input::initInput(void){

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	GraphicManager::GetInstance()->GetWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Permite ver el cursor
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	// insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
	//Inicializa en input para ser usado
	inputManager = OIS::InputManager::createInputSystem(pl);

	//Necesitamos coger input de los dispositivos:
	//Pasamos true para decir que son buffered (Recibimos eventos de mouseMoved,mousePressed,keyReleased...)
	keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

	mouse->setEventCallback(this);
	keyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(GraphicManager::GetInstance()->GetWindow());

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(GraphicManager::GetInstance()->GetWindow(), this);


}

bool Input::handleInput(void){

	//Captura el input del teclado y ratón
	keyboard->capture();
	mouse->capture();

	return true;
}

#pragma region Keyboard  

bool Input::keyPressed(const OIS::KeyEvent &arg){

	keys[arg.key] = true;

	return true;
}

bool Input::keyReleased(const OIS::KeyEvent &arg){

	keys[arg.key] = false;

	return true;
}

bool Input::getKey(OIS::KeyCode kc){
	return keys[kc];
}

#pragma endregion Keyboard

#pragma region Mouse  


MousePosition Input::getMousePosition(){
	return mousePosition;
}

bool Input::mouseMoved(const OIS::MouseEvent &arg){ //Mirar cómo va

	mousePosition.X = arg.state.X;
	mousePosition.Y = arg.state.Y;
	mousePosition.Z = arg.state.Z;

	return true;
}

bool Input::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	keysMouse[id] = true;
	return true;

}

bool Input::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	keysMouse[id] = false;

	return true;
}

bool Input::getMouseButton(OIS::MouseButtonID id){
	return keysMouse[id];
}

#pragma endregion Mouse

#pragma region Window Event Listener  

//Actualiza el estado del ratón a la nueva ventana
void Input::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Destruye OIS antes de que se cierre la ventana
void Input::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if (rw == GraphicManager::GetInstance()->GetWindow())
	{
		if (inputManager)
		{
			inputManager->destroyInputObject(mouse);
			inputManager->destroyInputObject(keyboard);

			OIS::InputManager::destroyInputSystem(inputManager);
			inputManager = 0;
		}
	}
}

#pragma endregion Window Event Listener

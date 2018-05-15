#include "InputManager.h"


InputManager::InputManager() : mInputManager(0), mMouse(0), mKeyboard(0)
{
}


InputManager::~InputManager()
{
}


InputManager *InputManager::instance = 0;

InputManager *InputManager::getInstance()
{
	if (!instance)
		instance = new InputManager;
	return instance;

}

void InputManager::capture(){
	//Need to capture/update each device
	mKeyboard->capture(); // Accede al KeyPressed de todos los KeyListeners
	mMouse->capture();
}

bool InputManager::getKeyDown(const OIS::KeyCode & keycode){
	return (mKeyboard->isKeyDown(keycode));
}

bool InputManager::getMouseButtonDown(OIS::MouseButtonID id){
	return (mMouse->getMouseState().buttonDown(id));
}
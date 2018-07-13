#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <OIS.h>
#include <Ogre.h>
static class InputManager 
{
protected:
	//---------------------------ATRIBUTOS--------------------------------
	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	static InputManager * instance;
	//---------------------------ATRIBUTOS--------------------------------

public:

	InputManager();
	~InputManager();
	static InputManager* getInstance();
	void capture();
	//Teclado
	bool getKeyDown(const OIS::KeyCode & keycode);
	bool getMouseButtonDown(OIS::MouseButtonID id);


	//Devuelve las coordenadas del ratón
	Ogre::Vector2 getMouseCoordinates(){ return Ogre::Vector2(mMouse->getMouseState().X.abs, mMouse->getMouseState().Y.abs); };
	int getMouseCoordinateX(){ return mMouse->getMouseState().X.abs; };
	int getMouseCoordinateY(){ return mMouse->getMouseState().Y.abs; };


protected:



};

#endif /* INPUTMANAGER_H_ */
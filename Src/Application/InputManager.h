#ifndef __Input_h_
#define __Input_h_

#include <OIS.h>
#include <OgreWindowEventUtilities.h>

#define NUMKEYS 256
#define NUMKEYMOUSE 8

//Estructura que contiene las coordenadas del ratón
struct MousePosition{
	OIS::Axis X, Y, Z;
};

class Input : public OIS::MouseListener, public OIS::KeyListener, public Ogre::WindowEventListener
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static Input *instance;

public:
	/* Static access method. */
	static Input * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	OIS::InputManager* inputManager;

public:
	void initInput(void);
	bool handleInput(void);

private:
	Input();
	~Input();

	virtual void windowResized(Ogre::RenderWindow* rw);	//Se le llama cada vez que se escala la ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);	//Destruye OIS antes de que se cierre la ventana

#pragma region Keyboard 
private:
	std::vector<bool> keys;		//Vector para guardar las teclas del teclado
	OIS::Keyboard* keyboard;

public:
	//Guarda las teclas recibidas por OIS en la estructura
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	//Comprueba si la tecla que está en la estructura coincide con la consultada
	bool getKey(OIS::KeyCode kc);

#pragma endregion Keyboard

#pragma region Mouse  
private:
	std::vector<bool> keysMouse;	//Vector para guardar las teclas del ratón
	OIS::Mouse* mouse;
	MousePosition mousePosition;

public:
	//Devuelve la posición del ratón en la ventana
	MousePosition getMousePosition();

	//Comprueba si la tecla del ratón que está en la estructura coincide con la consultada
	bool Input::getMouseButton(OIS::MouseButtonID id);

	//Guarda las teclas del ratón recibidas por OIS en la estructura
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

#pragma endregion Mouse


};
#endif // #ifndef __Input_h_

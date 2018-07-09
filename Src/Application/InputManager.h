#ifndef __Input_h_
#define __Input_h_

#include <OIS.h>
#include <OgreWindowEventUtilities.h>

#define NUMKEYS 145
#define NUMKEYMOUSE 3

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

	//Vectores para guardar las teclas del teclado y los botones del ratón
	std::vector<bool> keys;
	std::vector<bool> keysMouse;

	OIS::InputManager* inputManager;
	OIS::Mouse*    mouse;
	OIS::Keyboard* keyboard;

	MousePosition mousePosition;


public:
	void initInput(void);
	bool handleInput(void);

#pragma region Keyboard 

	//Guarda las teclas recibidas por OIS en la estructura
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	//Comprueba si la tecla que está en la estructura coincide con la consultada
	bool getKey(OIS::KeyCode kc);

#pragma endregion Keyboard

#pragma region Mouse  

	//Devuelve la posición del ratón en la ventana
	MousePosition getMousePosition();

	//Comprueba si la tecla del ratón que está en la estructura coincide con la consultada
	bool Input::getMouseButton(OIS::MouseButtonID id);

	//Guarda las teclas del ratón recibidas por OIS en la estructura
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);


#pragma endregion Mouse

private:

	//Se le llama cada vez que se escala la ventana
	virtual void windowResized(Ogre::RenderWindow* rw);

	//Destruye OIS antes de que se cierre la ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);

	Input();
	~Input();


};
#endif // #ifndef __Input_h_

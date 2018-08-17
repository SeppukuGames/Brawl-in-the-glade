#ifndef __Input_h_
#define __Input_h_

#include <OIS.h>
#include <OgreWindowEventUtilities.h>

#define NUMKEYS 256		//Número de teclas del teclado
#define NUMKEYMOUSE 8	//Número de botones del ratón

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
	void initInput(void);					//Método encargado de inicializar el input
	bool handleInput(void);					//Método encargado de detectar el input

private:
	Input();
	~Input();

	virtual void windowResized(Ogre::RenderWindow* rw);			//Actualiza el estado del ratón a la nueva ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);			//Destruye OIS antes de que se cierre la ventana

#pragma region Keyboard 
private:
	std::vector<bool> keys;		//Vector para guardar las teclas del teclado
	OIS::Keyboard* keyboard;	//Atributo para hacer referencia del teclado

public:

	//Guarda las teclas recibidas por OIS en la estructura
	bool keyPressed(const OIS::KeyEvent &arg);						//Método que devuelve true si se ha pulsado la tecla recibida como parámetro
	bool keyReleased(const OIS::KeyEvent &arg);						//Método que devuelve true si se ha soltado la tecla recibida como parámetro
	bool getKey(OIS::KeyCode kc);									//Comprueba si la tecla que está en la estructura coincide con la consultada

#pragma endregion Keyboard

#pragma region Mouse  
private:
	std::vector<bool> keysMouse;	//Vector para guardar las teclas del ratón
	OIS::Mouse* mouse;				//Referencia del ratón
	MousePosition mousePosition;	//Posición del ratón

public:
	MousePosition getMousePosition();				//Devuelve la posición del ratón en la ventana
	bool getMouseButton(OIS::MouseButtonID id);		//Comprueba si el botón del ratón que está en la estructura coincide con la consultada

	//Guarda las teclas del ratón recibidas por OIS en la estructura
	bool mouseMoved(const OIS::MouseEvent &arg);							//Método que comprueba si se ha movido el ratón y guarda la posición
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);	//Método que devuelve true si se ha pulsado el botón del ratón recibido como parámetro 
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);	//Método que devuelve true si se ha soltado el botón del ratón recibido como parámetro

#pragma endregion Mouse


};
#endif // #ifndef __Input_h_

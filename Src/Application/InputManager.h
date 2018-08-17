#ifndef __Input_h_
#define __Input_h_

#include <OIS.h>
#include <OgreWindowEventUtilities.h>

#define NUMKEYS 256		//N�mero de teclas del teclado
#define NUMKEYMOUSE 8	//N�mero de botones del rat�n

//Estructura que contiene las coordenadas del rat�n
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
	void initInput(void);					//M�todo encargado de inicializar el input
	bool handleInput(void);					//M�todo encargado de detectar el input

private:
	Input();
	~Input();

	virtual void windowResized(Ogre::RenderWindow* rw);			//Actualiza el estado del rat�n a la nueva ventana
	virtual void windowClosed(Ogre::RenderWindow* rw);			//Destruye OIS antes de que se cierre la ventana

#pragma region Keyboard 
private:
	std::vector<bool> keys;		//Vector para guardar las teclas del teclado
	OIS::Keyboard* keyboard;	//Atributo para hacer referencia del teclado

public:

	//Guarda las teclas recibidas por OIS en la estructura
	bool keyPressed(const OIS::KeyEvent &arg);						//M�todo que devuelve true si se ha pulsado la tecla recibida como par�metro
	bool keyReleased(const OIS::KeyEvent &arg);						//M�todo que devuelve true si se ha soltado la tecla recibida como par�metro
	bool getKey(OIS::KeyCode kc);									//Comprueba si la tecla que est� en la estructura coincide con la consultada

#pragma endregion Keyboard

#pragma region Mouse  
private:
	std::vector<bool> keysMouse;	//Vector para guardar las teclas del rat�n
	OIS::Mouse* mouse;				//Referencia del rat�n
	MousePosition mousePosition;	//Posici�n del rat�n

public:
	MousePosition getMousePosition();				//Devuelve la posici�n del rat�n en la ventana
	bool getMouseButton(OIS::MouseButtonID id);		//Comprueba si el bot�n del rat�n que est� en la estructura coincide con la consultada

	//Guarda las teclas del rat�n recibidas por OIS en la estructura
	bool mouseMoved(const OIS::MouseEvent &arg);							//M�todo que comprueba si se ha movido el rat�n y guarda la posici�n
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);	//M�todo que devuelve true si se ha pulsado el bot�n del rat�n recibido como par�metro 
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);	//M�todo que devuelve true si se ha soltado el bot�n del rat�n recibido como par�metro

#pragma endregion Mouse


};
#endif // #ifndef __Input_h_

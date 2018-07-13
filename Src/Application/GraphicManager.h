#ifndef __GraphicManager_h_
#define __GraphicManager_h_

#include <OgreRoot.h>
#include <OgreOverlaySystem.h>

class GraphicManager
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static GraphicManager *instance;

public:
	/* Static access method. */
	static GraphicManager * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	//Permite inicializar el core de Ogre facilmente
	Ogre::Root *root;

	//Strings que utilizaremos durante el setup
	Ogre::String resourcesCfg;
	Ogre::String pluginsCfg;

	//RenderSystem
	Ogre::RenderWindow* window;

	//GUI
	Ogre::OverlaySystem *overlaySystem;	

public:

	void InitGraphics(void);			//M�todo que inicializa los recursos y los plugings
	bool Render(void);					//M�todo utilizado para poder renderizar.Devuelve falso si da error

	inline Ogre::Root* GetRoot(){ return root; };								//M�todo que devuelve el root 
	inline Ogre::RenderWindow* GetWindow(){ return window; };					//M�todo que devuelve la ventana
	inline Ogre::OverlaySystem* GetOverlaySystem(){ return overlaySystem; };	//M�todo que devuelve el sistema de overlay

private:
	//Constructora privada para prevenir instanciaci�n 
	GraphicManager();
	~GraphicManager();

	bool Setup();
	bool Configure(void);				//Configura el RenderSystem y crea la ventana
	void SetupResources(void);			//Establece los recursos potencialmente utilizables. Para a�adir nuevos recursos : resources.cfg
	void LoadResources(void);			//Carga todos los recursos

};
#endif // #ifndef __GraphicManager_h_

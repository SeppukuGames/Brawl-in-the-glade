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
	/*
	Ciclo básico de Ogre:

	Create the Ogre::Root object
	Define the resources that Ogre will use
	Choose and set up the RenderSystem (DirectX, OpenGL, etc)
	Create the RenderWindow
	Set up any third party libraries and plugins.
	Initialise resources
	Register listener classes
	Build a scene
	Start the render loop
	*/

	void InitGraphics(void);
	bool Render(void);

	inline Ogre::Root* GetRoot(){ return root; };
	inline Ogre::RenderWindow* GetWindow(){ return window; };
	inline Ogre::OverlaySystem* GetOverlaySystem(){ return overlaySystem; };

private:
	/* Private constructor to prevent instancing. */
	GraphicManager();
	~GraphicManager();

	bool Setup();
	bool Configure(void);//Configura el RenderSystem y crea la ventana
	void SetupResources(void);//Establece los recursos potencialmente utilizables. Para añadir nuevos recursos : resources.cfg
	void LoadResources(void);//Carga todos los recursos

};
#endif // #ifndef __GraphicManager_h_

/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "BaseApplication.h"
#include <OgreException.h>

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
:	mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),

	mCamera(0),
	mSceneMgr(0),
	mWindow(0),

	mCursorWasVisible(false),
	mShutDown(false),
	mInputManager(0),
	mMouse(0),
	mKeyboard(0)
	//mOverlaySystem(0)
{
}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
	//if (mOverlaySystem) delete mOverlaySystem;

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

//-------------------------------------------------------------------------------------

void BaseApplication::go(void)
{
	//Strings que identifican los archivos de recursos y de plugins
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "Ogre/resources.cfg";
	mPluginsCfg = "Ogre/plugins.cfg";
#endif

	if (!setup())
		return;

	while (renderLoop());
	//Le cedemos el control a Ogre
	//mRoot->startRendering();

	// clean up
	destroyScene();
}
//-------------------------------------------------------------------------------------

//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame
bool BaseApplication::renderLoop()
{
	//Actualiza el RenderWindow
	Ogre::WindowEventUtilities::messagePump();

	if (mWindow->isClosed()) return false;

	//Se profundiza en el TUTORIAL4
	if (!mRoot->renderOneFrame()) return false;
}

//-------------------------------------------------------------------------------------

bool BaseApplication::setup(void)
{
	//Creamos la instancia del root object
	//Tiene 3 par�metros (pluginFileName,configFileName,logFileName), los 2 ultimos tienen los valores por defecto correctos
	mRoot = new Ogre::Root(mPluginsCfg);

	//Establecemos los recursos: Para incluir nuevos recursos, tocar resources.cfg
	//No los inicializa, solo establece donde buscar los potenciales recursos
	setupResources();

	//Configuramos el renderSystem y creamos la ventana
	bool carryOn = configure();
	if (!carryOn) return false;

	//Carga todos los recursos
	loadResources();
	// Create any resource listeners (for loading screens)
	//createResourceListener();

	chooseSceneManager();
	createCamera();
	createViewports();

	//Creamos la Escena del m�todo hijo
	createScene();

	initOIS();
	createFrameListener();

	return true;
};

//-------------------------------------------------------------------------------------
//Establece los recursos potencialmente utilizables. Para a�adir nuevos recursos : resources.cfg
void BaseApplication::setupResources(void)
{
	//Carga las rutas de los recursos del archivo de configuraci�n
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	//Tenemos que recorrer todas las secciones del archivo [Essential] y a�adir las localizaciones al ResourceGroupManager
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	//String auxiliares para guardar informaci�n del archivo de configuracion parseado

	Ogre::String pathName;//Ruta de los recursos
	Ogre::String formatName;//Formato del archivo (Zip, Filesystem)

	Ogre::String secName;

	//Iteramos a trav�s de todos los elementos
	while (secIt.hasMoreElements())
	{
		secName = secIt.peekNextKey();

		//Preguntamos por un iterador que nos permitir� iterar a traves de los elementos de cada secci�n
		Ogre::ConfigFile::SettingsMultiMap *settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		//Iteramos escaneando cada elemento
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			//Desempaquetamos cada par
			formatName = it->first;
			pathName = it->second;

			//A�adimos la localizaci�n al ResourceGroupManager
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				pathName, formatName, secName);
		}
	}
}

//-------------------------------------------------------------------------------------
//Configura el RenderSystem y crea la ventana
bool BaseApplication::configure(void)
{
	//El config Dialog permite hacer ajustes e inicializa el sistema
	//Podemos hacer que el configDialog solo salga si no hay un ogre.cfg
	//Primero trata de recuperar el cfg y si no lo encuentra, crea el configDialog
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;
		/*Tal vez deber�amos lanzar una excepci�n en vez de salir de la aplicaci�n
		, borrando ogre.cfg del bloque de cache, porque puede desencadenar errores */

	//Se pueden ajustar los valores manualmente
	//Podemos utilizarlo para crear dentro del juego nuestro propia menu de ajustes, que puede manejar el renderSYstem y los atajos de teclado
	//Ejemplo de inicializar Direct3D9 Render System
	/*
	//Do not add this to your project
	RenderSystem* rs = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");

	mRoot->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	//Root::getAvailableRenderers permite saber qu� renderers est�n disponibles en nuestro sistema

	//RenderSystem::getConfigOptions permite ver las opciones que ofrece un RenderSystem
	*/

	//Creamos la RenderWindow por defecto
	mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

	//Podemos crear la ventana con win32 API, Ejemplo:
	/*
	// Do not add this to your project
	mRoot->initialise(false);

	HWND hWnd = 0;

	// Retrieve the HWND for the window we want to render in.
	// This step depends entirely on the windowing system you are using.

	NameValuePairList misc;
	misc["externalWindowHandle"] = StringConverter::toString((int)hWnd);

	//Aplicamos a mroot los cambios que hemos hecho
	RenderWindow* win = mRoot->createRenderWindow("Main RenderWindow", 800, 600, false, &misc);
	*/
}
//-------------------------------------------------------------------------------------

//Carga todos los recursos
void BaseApplication::loadResources(void)
{
	//Cargamos todos los recursos. Para m�s profundidad en el tema y cargar los recursos solo cuando los necesitamos, habr� que mirar TUTORIALES DEPTH
	
	//Establecemos el n�mero por defecto de mipmaps que se usar�n.
	//Permite utilizar diferentes niveles de detalles para texturas dependiendo de lo lejos que est� de la c�mara
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//Inicializa todos los recursos encontrados por Ogre
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

//-------------------------------------------------------------------------------------

void BaseApplication::chooseSceneManager(void)
{
	//Creamos el SceneManager
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	/*No lo utilizamos?? 
	// Inicializa el OverlaySystem
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
	*/
}

//-------------------------------------------------------------------------------------

void BaseApplication::createCamera(void)
{
	//Creamos la c�mara
	mCamera = mSceneMgr->createCamera("MainCam");

	//La inicializamos
	mCamera->setPosition(Ogre::Vector3(0, 0, 80));
	mCamera->lookAt(Ogre::Vector3(0, 0, -300));
	mCamera->setNearClipDistance(5);
}

//-------------------------------------------------------------------------------------

void BaseApplication::createViewports(void)
{
	//Creamos un viewport, toda la ventana
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------

//Inicializa el input
void BaseApplication::initOIS(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Permite ver el cursor
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	//Inicializa en input para ser usado
	mInputManager = OIS::InputManager::createInputSystem(pl);

	//Necesitamos coger input de los dispositivos:
	//Pasamos true para decir que son buffered (Recibimos eventos de mouseMoved,mousePressed,keyReleased...)
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
}

void BaseApplication::createFrameListener(void)
{


	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------


bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;

	if (mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	return true;
}
//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
	{
	}
	else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
	{
		
	}
	else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
	{
		
	}
	else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
	{
		Ogre::PolygonMode pm;

		switch (mCamera->getPolygonMode())
		{
		case Ogre::PM_SOLID:
			pm = Ogre::PM_WIREFRAME;
			break;
		case Ogre::PM_WIREFRAME:
			pm = Ogre::PM_POINTS;
			break;
		default:
			pm = Ogre::PM_SOLID;
		}

		mCamera->setPolygonMode(pm);
	}
	else if (arg.key == OIS::KC_F5)   // refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	}
	else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
	{
		mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	return true;
}

bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if (rw == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}
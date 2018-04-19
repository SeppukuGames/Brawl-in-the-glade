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
#include <OgreTimer.h>

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif


using namespace irrklang;

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
	: mRoot(0),
	mResourcesCfg(Ogre::BLANKSTRING),
	mPluginsCfg(Ogre::BLANKSTRING),

	mWindow(0),

	mSceneMgr(0),
	mCamera(0),

	mInputManager(0),
	mMouse(0),
	mKeyboard(0),

	//mCursorWasVisible(false),
	mShutDown(false)
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
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;

	timer = new Ogre::Timer();
	lastTime = timer->getMilliseconds();
	while (gameLoop());
	//Le cedemos el control a Ogre
	//mRoot->startRendering();

	// clean up
	destroyScene();
}
//-------------------------------------------------------------------------------------

//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame
bool BaseApplication::gameLoop()
{
	//Actualiza el RenderWindow
	Ogre::WindowEventUtilities::messagePump();

	if (mWindow->isClosed()) return false;

	double current = timer->getMilliseconds();
	double elapsed = (current - lastTime) /1000 ;

	if (!handleInput())
		return false;

	/// Reset all of our timers
	time_physics_prev = time_physics_curr = getMilliseconds();
	time_gameclock = getMilliseconds();
	update(elapsed);

	if (!render())
		return false;

	lastTime = current;


	return true;	//Return true puesto.

}

//Detecta input
bool BaseApplication::handleInput(void){

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (mShutDown)
		return false;

	return true;
}

//Detecta input
bool BaseApplication::update(double elapsed)
{
	//Actualiza todos los objetos
	for (size_t i = 0; i < actors_.size(); i++)
		actors_[i]->tick(elapsed);

	if (this->physicsEngine != NULL){		
		int maxSubSteps = 1;
		btScalar fixedTimeStep = btScalar(1.0) / btScalar(60.0); //suppose you have 60 frames per second
		physicsEngine->getDynamicsWorld()->stepSimulation(fixedTimeStep);

		for (int i = 0; i < this->physicsEngine->getCollisionObjectCount(); i++) {
			//Obtiene referencia al rigidbody correspondiente
			btCollisionObject* obj = this->physicsEngine->getDynamicsWorld()->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);

			if (body && body->getMotionState()){
				//Cogemos el transform del estado del rigidbody correspondiente
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);

				//Decir a Ogre que cambie el nodo de posición
				void *userPointer = body->getUserPointer();
				if (userPointer) {
					btQuaternion orientation = trans.getRotation();
					Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
					sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
					sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				}
			}
		}
	}



	return true;
}

//Detecta input
bool BaseApplication::render(void){

	//Se profundiza en el TUTORIAL4
	if (!mRoot->renderOneFrame()) return false;

	return true;
}


//-------------------------------------------------------------------------------------

bool BaseApplication::setup(void)
{
	//Creamos la instancia del root object
	//Tiene 3 parámetros (pluginFileName,configFileName,logFileName), los 2 ultimos tienen los valores por defecto correctos
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

	physicsEngine = new Physics();
	initSoundEngine();
	//Creamos la Escena del método hijo
	createScene();

	initOIS();
	//createFrameListener();

	return true;
};

//-------------------------------------------------------------------------------------
//HAY QUE ELIMINAR LOS WARNINGS DE AQUI
//Establece los recursos potencialmente utilizables. Para añadir nuevos recursos : resources.cfg
void BaseApplication::setupResources(void)
{
	//Carga las rutas de los recursos del archivo de configuración
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	//Tenemos que recorrer todas las secciones del archivo [Essential] y añadir las localizaciones al ResourceGroupManager
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	//String auxiliares para guardar información del archivo de configuracion parseado

	Ogre::String pathName;//Ruta de los recursos
	Ogre::String formatName;//Formato del archivo (Zip, Filesystem)

	Ogre::String secName;

	//Iteramos a través de todos los elementos
	while (secIt.hasMoreElements())
	{
		secName = secIt.peekNextKey();

		//Preguntamos por un iterador que nos permitirá iterar a traves de los elementos de cada sección
		Ogre::ConfigFile::SettingsMultiMap *settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		//Iteramos escaneando cada elemento
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			//Desempaquetamos cada par
			formatName = it->first;
			pathName = it->second;

			//Añadimos la localización al ResourceGroupManager
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
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog(NULL)))
		return false;
	/*Tal vez deberíamos lanzar una excepción en vez de salir de la aplicación
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

	//Root::getAvailableRenderers permite saber qué renderers están disponibles en nuestro sistema

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

	return true;
}
//-------------------------------------------------------------------------------------

//Carga todos los recursos
void BaseApplication::loadResources(void)
{
	//Cargamos todos los recursos. Para más profundidad en el tema y cargar los recursos solo cuando los necesitamos, habrá que mirar TUTORIALES DEPTH

	//Establecemos el número por defecto de mipmaps que se usarán.
	//Permite utilizar diferentes niveles de detalles para texturas dependiendo de lo lejos que esté de la cámara
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//Inicializa todos los recursos encontrados por Ogre
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

//-------------------------------------------------------------------------------------

void BaseApplication::chooseSceneManager(void)
{
	//Creamos el SceneManager
	mSceneMgr = mRoot->createSceneManager();

	/*No lo utilizamos??
	// Inicializa el OverlaySystem
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
	*/
}

//-------------------------------------------------------------------------------------

void BaseApplication::createCamera(void)
{
	//Creamos la cámara
	mCamera = mSceneMgr->createCamera("MainCam");

	//La inicializamos
	mCamera->setPosition(Ogre::Vector3(0, 200, 100));
	mCamera->lookAt(Ogre::Vector3(0, -80, -300));
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

void BaseApplication::initSoundEngine(void)
{
	// start the sound engine with default parameters
	soundEngine = createIrrKlangDevice();

	if (!soundEngine)
	{
		printf("Could not startup engine\n");
	}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped

	soundEngine->play2D("../../Media/Sounds/getout.ogg", true);


	// play a single sound
	soundEngine->play2D("../../Media/Sounds/bell.wav");

	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	//engine->drop(); // delete engine

}
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
	mInputManager = OIS::InputManager::createInputSystem(pl);

	//Necesitamos coger input de los dispositivos:
	//Pasamos true para decir que son buffered (Recibimos eventos de mouseMoved,mousePressed,keyReleased...)
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}


//----------------Window Event Listener---------------

//Actualiza el estado del ratón a la nueva ventana
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Destruye OIS antes de que se cierre la ventana
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

//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------



//--------------------OIS-------------------------------

bool BaseApplication::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}
	else if (arg.key == OIS::KC_A)
	{
		int a = 0;
	}
	

	for (size_t i = 0; i < keyInputObservers.size(); i++)
		keyInputObservers[i]->keyPressed(arg);

	return true;
}

bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{

	for (size_t i = 0; i < keyInputObservers.size(); i++)
		keyInputObservers[i]->keyReleased(arg);

	return true;
}

bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
	for (int i = 0; i < keyInputObservers.size(); i++)
		mouseInputObservers[i]->mouseMoved(arg);
	return true;
}

bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for (int i = 0; i < keyInputObservers.size(); i++)
		mouseInputObservers[i]->mousePressed(arg, id);
	return true;
}

bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for (int i = 0; i < keyInputObservers.size(); i++)
		mouseInputObservers[i]->mouseReleased(arg, id);
	return true;
}

void BaseApplication::registerKeyInputObserver(OIS::KeyListener *observer)
{
	keyInputObservers.push_back(observer);
}


void BaseApplication::registerMouseInputObserver(OIS::MouseListener *observer)
{
	mouseInputObservers.push_back(observer);
}


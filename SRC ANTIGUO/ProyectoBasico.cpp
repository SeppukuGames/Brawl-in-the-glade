/*
#include "ProyectoBasico.h"


Game::Game() : mRoot(0), mResourcesCfg(Ogre::StringUtil::BLANK), mPluginsCfg(Ogre::StringUtil::BLANK)
{
}


Game::~Game()
{
	//Nos eliminamos como Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);


	delete mRoot;
}

bool Game::go(){

#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "Ogre/resources.cfg";
	mPluginsCfg = "Ogre/plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);


	//------------------------------------------------------------------------------------------------------
	//Setting UP Resources 

	//Parsing the config file into the system.
	cf.load(mResourcesCfg);


	//name: Path to resources in disk,
	//loctype: defines what kind of location the element is (e.g. Filesystem, zip..)
	Ogre::String name, locType;

	//We now iterate through rach section in the resources.cfg.
	//Sections are signaled as [NAME]
	
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		//Now we are iterating INSIDE the section [secIt]
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;

			//We now know the type of the element and its path.
			//We add it as a location to the Resource Group Manager
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
			std::cout << "inserting:\n";
			std::cout << name << locType << std::endl;
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	// Render System Config

	//If there is no previous Ogre.cfg, this displays the config dialog
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	//------------------------------------------------------------------------------------------------------
	//Render Window Creation
	mWindow = mRoot->initialise(true, "OGRE3D Game");

	//------------------------------------------------------------------------------------------------------
	//Resources Init

	//We are only going to use 5 mimpams at a time. Mipmaps are efficent ways to save a texture.
	//Taking only 1/3 more of space, we can have several sizes of the texture to choose from.
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//Now we init every resource previously added
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//------------------------------------------------------------------------------------------------------
	//SceneManager Set Up

	//we generate the default sceneManager. (more SceneManagers in Ogre::ST_....)
	scnMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	//------------------------------------------------------------------------------------------------------
	//Camera Creation

	//Self-explanatory methods
	cam = scnMgr->createCamera("MainCam");
	cam->setPosition(0, 0, 80);
	cam->lookAt(0, 0, -300);
	cam->setNearClipDistance(5);


	//------------------------------------------------------------------------------------------------------
	//ViewPort Addition
	vp = mWindow->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(150, 150, 150));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	//------------------------------------------------------------------------------------------------------
	//Scene SetUp
	try{

		Ogre::Entity * ogrito = scnMgr->createEntity("ogrehead.mesh");
		Ogre::SceneNode * ogritoNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		ogritoNode->attachObject(ogrito);
	}
	catch (Ogre::FileNotFoundException e){
		std::string a = e.getFullDescription();
		std::cout << a;
	}
	scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	light = scnMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);


	//INIT OIS

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	//Input de teclado y ratón - Unbuffered keyboard, mouse
	//Si queremos usar buffered input (queremos obtener callbacks para mouseMoved, mousePressed, keyRelease, etc)
	//Tendríamos que poner el segundo parámetro de createinputObject a true

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));


	//Inicializa el área de click del ratón al de la ventana
	windowResized(mWindow);

	//Registramos el WindowEventListener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);


	//RENDERING LOOP

	mRoot->addFrameListener(this);
	mRoot->startRendering();
	//Ogre::WindowEventUtilities::messagePump();
	//if (mWindow->isClosed())return false;
	//if (!mRoot->renderOneFrame())return false;
	


	return true;

}

/*bool Game::loop(){

	while (true)
	{
		Ogre::WindowEventUtilities::messagePump();
		if (mWindow->isClosed())return false;
		if (!root->renderOneFrame())return false;
	}

	}*//*

//---------------------------OIS - EVENTOS DE TECLADO Y RATÓN---------------------
//Ajusta el área de clipping del ratón
//A este método se le llama cada vez que se reescala el tamaño de la ventana y se asegura de que
//el estado de ratón de OIS está sincronizado con el tamaño de la ventana
void Game::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


//Destruye OIS cuando se cierra la ventana
void Game::windowClosed(Ogre::RenderWindow* rw)
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

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	return true;
}

//---------------------------OIS - EVENTOS DE TECLADO Y RATÓN---------------------



void Game::close(){

}




#ifdef _DEBUG || !_WIN32
int main(){
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){

#endif

	Game * game = new Game();
	game->go();
	//game->loop();
	game->close();
	delete game;
	return 0;
}
*/
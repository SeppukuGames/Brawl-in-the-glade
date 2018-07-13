#include "GraphicManager.h"
#include <OgreConfigFile.h> //Para parsear los .cfg
#include <OgreTextureManager.h>
#include <OgreRenderWindow.h>


#pragma region Singleton  

/* Null, because instance will be initialized on demand. */
GraphicManager* GraphicManager::instance = 0;

GraphicManager* GraphicManager::GetInstance()
{
	if (instance == 0)
		instance = new GraphicManager();

	return instance;
}

void GraphicManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

GraphicManager::GraphicManager() :
root(0),
resourcesCfg(Ogre::BLANKSTRING),
pluginsCfg(Ogre::BLANKSTRING),
window(0),
overlaySystem(0)
{
}

GraphicManager::~GraphicManager()
{
	if (overlaySystem)
		delete overlaySystem;
	overlaySystem = nullptr;

	//�ltimo en borrar,es el m�s importante
	delete root;
	root = nullptr;
}

//M�todo que inicializa los recursos y los plugings
void GraphicManager::InitGraphics(void)
{
	//Strings que identifican los archivos de recursos y de plugins
#ifdef _DEBUG
	resourcesCfg = "resources_d.cfg";
	pluginsCfg = "plugins_d.cfg";
#else
	resourcesCfg = "resources.cfg";
	pluginsCfg = "plugins.cfg";
#endif

	if (!Setup())
		return;
}

//M�todo utilizado para poder renderizar.Devuelve falso si da error
bool GraphicManager::Render(void) {
	return root->renderOneFrame();
}

bool GraphicManager::Setup(void)
{
	//Creamos la instancia del root object
	//Tiene 3 par�metros (pluginFileName,configFileName,logFileName), los 2 ultimos tienen los valores por defecto correctos
	root = new Ogre::Root(pluginsCfg);

	//Configuramos el renderSystem y creamos la ventana
	if (!Configure())
		return false;

	overlaySystem = new Ogre::OverlaySystem();

	//Establecemos los recursos: Para incluir nuevos recursos, tocar resources.cfg
	//No los inicializa, solo establece donde buscar los potenciales recursos
	SetupResources();

	//Carga todos los recursos
	LoadResources();

	return true;
};

//Configura el RenderSystem y crea la ventana
bool GraphicManager::Configure(void)
{
	//El config Dialog permite hacer ajustes e inicializa el sistema
	//Podemos hacer que el configDialog solo salga si no hay un ogre.cfg
	//Primero trata de recuperar el cfg y si no lo encuentra, crea el configDialog
	if (!(root->restoreConfig() || root->showConfigDialog(NULL)))
		return false;


	/*Tal vez deber�amos lanzar una excepci�n en vez de salir de la aplicaci�n
	, borrando ogre.cfg del bloque de cache, porque puede desencadenar errores 

	//Se pueden ajustar los valores manualmente
	//Podemos utilizarlo para crear dentro del juego nuestro propia menu de ajustes, que puede manejar el renderSYstem y los atajos de teclado
	//Ejemplo de inicializar Direct3D9 Render System
	
	//Do not add this to your project
	RenderSystem* rs = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");

	mRoot->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	//Root::getAvailableRenderers permite saber qu� renderers est�n disponibles en nuestro sistema

	//RenderSystem::getConfigOptions permite ver las opciones que ofrece un RenderSystem
	
	//Podemos crear la ventana con win32 API, Ejemplo:
	
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

	//Creamos la RenderWindow por defecto
	window = root->initialise(true, "Brawl in the glade");

	return true;
}

//Establece los recursos potencialmente utilizables. Para a�adir nuevos recursos : resources.cfg
void GraphicManager::SetupResources(void)
{
	//Carga las rutas de los recursos del archivo de configuraci�n
	Ogre::ConfigFile cf;
	cf.load(resourcesCfg);

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

//Carga todos los recursos
void GraphicManager::LoadResources(void)
{
	//Establecemos el n�mero por defecto de mipmaps que se usar�n.
	//Permite utilizar diferentes niveles de detalles para texturas dependiendo de lo lejos que est� de la c�mara
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//Inicializa todos los recursos encontrados por Ogre
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


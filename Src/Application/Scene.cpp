#include "Scene.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include "GraphicManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "Error.h"

Scene::Scene() :
camera(0), sceneMgr(0)
{
	CreateSceneMgr();
	//Inicializamos Overlay
	InitOverlay();
}

Scene::~Scene()
{
	//Destruye todos los actores
	std::list <GameObject*> ::iterator it = actors.begin();
	
	for (it = actors.begin(); it != actors.end(); ++it){
		cout << "Estoy destruyendo una unidad de: " << (*it)->GetTag() << endl;
		delete (*it);
	}

	sceneMgr->clearScene();
}

//Método que crea el sceneManager
void Scene::CreateSceneMgr(void){

	sceneMgr = GraphicManager::GetInstance()->GetRoot()->createSceneManager();
}

// Método que inicializa el OverlaySystem
void Scene::InitOverlay(void)
{
	sceneMgr->addRenderQueueListener(GraphicManager::GetInstance()->GetOverlaySystem());
}

//Método encargado de añadir un GameObject
void Scene::AddGameObject(GameObject * gameObject){
	cout << "HE AÑADIDO: " << gameObject->GetTag() << " A LA ESCENA" << endl;
	actors.push_back(gameObject);
}


//Método que recibe un gameObject y lo añade a la cola de actores a destruir
void Scene::Destroy(GameObject * gameObject){
	actorsToDestroy.push(gameObject);//Se añade a la lista de actores a destruir
}

//Método que comprueba si un actor debe destruirse 
void Scene::CheckActorsDestruction(){
	//Comprobamos que no hay ningún actor por destruir
	while (!actorsToDestroy.empty()){

		//Caso en el que existe el gameObject
		if (std::find(actors.begin(), actors.end(), actorsToDestroy.back()) != actors.end()){
			actors.remove(actorsToDestroy.back());//Se elimina el gameObject de la lista de actores
			delete actorsToDestroy.back();
		}
		actorsToDestroy.pop();

	}
}
bool Scene::Tick(double elapsed)
{

	CheckActorsDestruction();
	PhysicsManager::GetInstance()->Tick();

	if (!HandleInput())
		return false;

	Update(elapsed);



	if (!Render())
		return false;

	return true;
}

void Scene::SetCamera(Ogre::Camera* cam) {
	camera = cam;
}


//Método encargado de establecer el viewport
void Scene::SetViewport(void)
{
	if (camera == nullptr)
		throw Error("No hay ningun GameObject con camara en la escena");
	//Creamos un viewport, toda la ventana
	Ogre::Viewport* vp = GraphicManager::GetInstance()->GetWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//Método encargado de detectar input
bool Scene::HandleInput(void) {
	return 	Input::GetInstance()->handleInput();
}


bool Scene::Update(double elapsed)
{
	/*std::list <GameObject*> ::iterator it;
	for (it = actors.begin(); it != actors.end(); ++it)
	(*it)->Tick(elapsed);

	return true;*/

	std::list <GameObject*> ::iterator it = actors.begin();
	while (it != actors.end()){
		GameObject* gameObject = (*it);
		++it;
		gameObject->Tick(elapsed);
	}

	return true;
}

bool Scene::Render(void) {
	return GraphicManager::GetInstance()->Render();
}


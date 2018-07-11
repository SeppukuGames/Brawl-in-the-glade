#include "Scene.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include "GraphicManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"

Scene::Scene() :
camera(0)
{
	sceneMgr = GraphicManager::GetInstance()->GetSceneManager();
}

Scene::~Scene()
{
	//TODO: Revisar cosas a destruir

	//Destruye todos los actores
	std::list <GameObject*> ::iterator it = actors.begin();
	while (!actors.empty() &&  it != actors.end()){
		delete (*it);
		actors.erase(it);

	}
}


void Scene::AddGameObject(GameObject * gameObject){
	actors.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject * gameObject){
	actors.remove(gameObject);
}

bool Scene::Tick(double elapsed)
{
	PhysicsManager::GetInstance()->Tick();

	if (!HandleInput())
		return false;

	Update(elapsed);

	if (!Render())
		return false;

	return true;
}

void Scene::SetViewport(void)
{
	//Creamos un viewport, toda la ventana
	Ogre::Viewport* vp = GraphicManager::GetInstance()->GetWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//Detecta input
bool Scene::HandleInput(void) {

	Input::GetInstance()->handleInput();

	//if (mShutDown)
	//	return false;

	return true;
}

//Detecta input
bool Scene::Update(double elapsed)
{
	std::list <GameObject*> ::iterator it = actors.begin();
	while (!actors.empty() && it != actors.end()){
		(*it)->Tick(elapsed);
		++it;

	}

	return true;
}

bool Scene::Render(void) {
	return GraphicManager::GetInstance()->Render();
}


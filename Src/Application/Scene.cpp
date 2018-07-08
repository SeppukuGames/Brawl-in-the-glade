#include "Scene.h"
#include "GraphicManager.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>

Scene::Scene() :
camera(0)
{
	sceneMgr = GraphicManager::GetInstance()->GetSceneManager();
}

Scene::~Scene()
{
	//TODO: Revisar cosas a destruir

	//Destruye todos los actores
	for (size_t i = 0; i < actors.size(); i++)
		delete(actors[i]);
}

void Scene::AddGameObject(GameObject * gameObject){
	actors.push_back(gameObject);
}

//TODO: Transformar en lista
void Scene::RemoveGameObject(GameObject * gameObject){

	int i = 0;
	std::vector<GameObject*>::iterator it = actors.begin();
	while (it < actors.end() && (*it)->GetNode()->getName() != gameObject->GetNode()->getName())
		it++;

	if (it < actors.end()){
		actors.erase(it);
	}

}

bool Scene::Tick(double elapsed)
{
	if (!HandleInput())
		return false;

	Update(elapsed);

	if (!Render())
		return false;

	return true;	//Return true puesto.
}

//Detecta input
bool Scene::HandleInput(void) {

	////Need to capture/update each device
	//mKeyboard->capture();
	//mMouse->capture();

	//if (mShutDown)
	//	return false;

	return true;
}

//Detecta input
bool Scene::Update(double elapsed)
{
	//Actualiza todos los objetos
	for (size_t i = 0; i < actors.size(); i++)
		actors[i]->Tick(elapsed);

	//TODO: FISICA

	return true;
}

//Detecta input
bool Scene::Render(void) {
	return GraphicManager::GetInstance()->Render();
}

void Scene::SetViewport(void)
{
	//Creamos un viewport, toda la ventana
	Ogre::Viewport* vp = GraphicManager::GetInstance()->GetWindow()->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
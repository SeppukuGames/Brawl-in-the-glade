#ifndef __Scene_h_
#define __Scene_h_

#include "GameObject.h"
#include <OgreRoot.h>
#include <list>

class Scene
{
#pragma region Attributes  
protected:
	Ogre::Camera* camera;

	//Todos los objetos de las escena
	std::list<GameObject*> actors;

	Ogre::SceneManager* sceneMgr;

#pragma endregion Attributes

#pragma region Methods  
public:
	Scene();
	~Scene();

	void AddGameObject(GameObject * gameObject);
	void RemoveGameObject(GameObject * gameObject);

	virtual bool Tick(double elapsed);//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame

	virtual void CreateScene(void) = 0; // Override me!

	Ogre::SceneManager * GetSceneMgr(){ return sceneMgr; };
	void SetViewport(void);

protected:
	virtual bool HandleInput(void);//Detecta input
	virtual bool Update(double elapsed);
	virtual bool Render(void);

	virtual void CreateSceneMgr(void); 
	virtual void InitOverlay(void);

#pragma endregion Methods

};
#endif // #ifndef __Scene_h_


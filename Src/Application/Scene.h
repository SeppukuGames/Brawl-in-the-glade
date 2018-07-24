#ifndef __Scene_h_
#define __Scene_h_

#include "GameObject.h"
#include <OgreRoot.h>
#include <list>

class Scene
{
#pragma region Attributes  
protected:
	Ogre::Camera* camera;				//Atributo para la referencia a la c�mara
	GameObject* player;					//Atributo para la referencia del jugador principal
	std::list<GameObject*> actors;		//Vector que guarda todos los objetos de las escena
	Ogre::SceneManager* sceneMgr;		//Atributo para la referencia del sceneManager

#pragma endregion Attributes

#pragma region Methods  
public:
	Scene();
	virtual ~Scene();

	void AddGameObject(GameObject * gameObject);				//M�todo encargado de a�adir un GameObject
	void RemoveGameObject(GameObject * gameObject);				//M�todo encargado de eliminar un GameObject

	virtual bool Tick(double elapsed);							//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame

	virtual void CreateScene(void) = 0;							//M�todo abstracto para crear una escena

	Ogre::SceneManager * GetSceneMgr(){ return sceneMgr; };		//M�todo que devuelve la referencia al sceneManager
	Ogre::Camera * GetCamera() { return camera; };
	void SetCamera(Ogre::Camera* cam);
	GameObject * GetPlayer() { return player; };
	void SetPlayer(GameObject* player);
	void SetViewport(void);										//M�todo encargado de establecer el viewport

protected:
	virtual bool HandleInput(void);								//M�todo encargado de detectar input
	virtual bool Update(double elapsed);						//Loop principal
	virtual bool Render(void);									//Renderizado
		
	virtual void CreateSceneMgr(void);							//M�todo que crea el sceneManager
	virtual void InitOverlay(void);								//M�todo que inicializa el OverlaySystem


#pragma endregion Methods

};
#endif // #ifndef __Scene_h_


#ifndef __Scene_h_
#define __Scene_h_

#include "GameObject.h"
#include <OgreRoot.h>
#include <list>

#include "lectorXML.h"

#include <queue>


class Scene
{
#pragma region Attributes  
protected:

	Ogre::Camera* camera;							//Atributo para la referencia a la c�mara
	std::list<GameObject*> actors;					//Vector que guarda todos los objetos de las escena
	std::queue<GameObject*> actorsToDestroy;		//Vector que guarda los objetos que se van a destruir en el siguiente tick
	Ogre::SceneManager* sceneMgr;					//Atributo para la referencia del sceneManager
	lectorXML lectorXML_;							//Lector de archivos XML
	bool stopCurrentUpdate = false;					//Detiene el update actual cuando se entra en pausa

#pragma endregion Attributes

#pragma region Methods  
public:
	Scene();
	virtual ~Scene();

	void AddGameObject(GameObject * gameObject);				//M�todo encargado de a�adir un GameObject
	void Destroy(GameObject * gameObject);						//M�todo que recibe un gameObject y lo a�ade a la cola de actores a destruir

	void CreateEnemies(int tipoEnemigo)
	{
		switch (tipoEnemigo)
		{
		case 0:
			lectorXML_.Leer("../enemy2.xml");
			break;
		case 1:
			lectorXML_.Leer("../enemy1.xml");
			break;

		case 2:
			lectorXML_.Leer("../enemies.xml");
			break;
		}
		
	}

	virtual bool Tick(double elapsed);							//Bucle principal. Acaba cuando se cierra la ventana o un error en renderOneFrame

	virtual void CreateScene(void) = 0;							//M�todo abstracto para crear una escena

	Ogre::SceneManager * GetSceneMgr(){ return sceneMgr; };		//M�todo que devuelve la referencia al sceneManager
	Ogre::Camera * GetCamera() { return camera; };

	void SetCamera(Ogre::Camera* cam);
	void SetViewport(void);										//M�todo encargado de establecer el viewport
	void setStopUpdate(bool ssu){ stopCurrentUpdate = ssu; }	//M�todo encargado de cambiar la pausa del update

protected:
	void CheckActorsDestruction();								//M�todo que comprueba si un actor debe destruirse 
	virtual bool HandleInput(void);								//M�todo encargado de detectar input
	virtual bool Update(double elapsed);						//Loop principal
	virtual bool Render(void);									//Renderizado
		
	virtual void CreateSceneMgr(void);							//M�todo que crea el sceneManager
	virtual void InitOverlay(void);								//M�todo que inicializa el OverlaySystem


#pragma endregion Methods

};
#endif // #ifndef __Scene_h_


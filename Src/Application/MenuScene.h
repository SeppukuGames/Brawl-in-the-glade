#ifndef __MenuScene_h_
#define __MenuScene_h_

#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	virtual void CreateScene(void);					//Método encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
};
#endif //


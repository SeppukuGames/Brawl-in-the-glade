#ifndef __Scene2_h_
#define __Scene2_h_

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2();
	virtual void CreateScene(void);					//Método encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
};
#endif // #ifndef __Scene2_h_


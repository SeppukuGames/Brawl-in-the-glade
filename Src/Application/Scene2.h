#ifndef __Scene2_h_
#define __Scene2_h_

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2();
	virtual void CreateScene(void);					//M�todo encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//M�todo encargado de crear las entidades (luz, c�mara, personaje, etc..)
};
#endif // #ifndef __Scene2_h_


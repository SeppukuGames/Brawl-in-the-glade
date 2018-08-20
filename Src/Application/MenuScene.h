#ifndef __MenuScene_h_
#define __MenuScene_h_

#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	virtual void CreateScene(void);					//M�todo encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//M�todo encargado de crear las entidades (luz, c�mara, personaje, etc..)
};
#endif //


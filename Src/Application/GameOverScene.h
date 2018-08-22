#ifndef __GameOverScene_h_
#define __GameOverScene_h_

#include "Scene.h"


class GameOverScene : public Scene
{
private:

public:
	GameOverScene();
	virtual void CreateScene(void);					//Método encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//Método encargado de crear las entidades (luz, cámara, personaje, etc..)
};
#endif // #ifndef __Scene1_h_
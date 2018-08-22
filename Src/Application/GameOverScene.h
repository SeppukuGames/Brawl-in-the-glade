#ifndef __GameOverScene_h_
#define __GameOverScene_h_

#include "Scene.h"


class GameOverScene : public Scene
{
private:

public:
	GameOverScene();
	virtual void CreateScene(void);					//M�todo encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//M�todo encargado de crear las entidades (luz, c�mara, personaje, etc..)
};
#endif // #ifndef __Scene1_h_
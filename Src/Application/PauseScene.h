#ifndef __PauseScene_h_
#define __PauseScene_h_

#include "Scene.h"


class PauseScene : public Scene
{
private:

public:		
	PauseScene();								
	bool Tick(double elapsed);
	virtual void CreateScene(void);				//Método encargado de crear la escena

protected:

	virtual void CreateGameObjects(void);			//Método encargado de crear las entidades (luz, cámara, personaje, etc..)


};
#endif // #ifndef __Scene1_h_


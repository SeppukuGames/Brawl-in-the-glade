#ifndef __PauseScene_h_
#define __PauseScene_h_

#include "Scene.h"


class PauseScene : public Scene
{
private:

public:		
	PauseScene();								
	bool Tick(double elapsed);
	virtual void CreateScene(void);				//M�todo encargado de crear la escena

protected:

	virtual void CreateGameObjects(void);			//M�todo encargado de crear las entidades (luz, c�mara, personaje, etc..)


};
#endif // #ifndef __Scene1_h_


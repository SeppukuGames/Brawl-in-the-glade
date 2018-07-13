#ifndef __Scene1_h_
#define __Scene1_h_

#include "Scene.h"


class Scene1 : public Scene
{
private:
	
public:
	Scene1();
	virtual void CreateScene(void);					//M�todo encargado de crear la escena

protected:
	virtual void CreateGameObjects(void);			//M�todo encargado de crear las entidades (luz, c�mara, personaje, etc..)
};
#endif // #ifndef __Scene1_h_


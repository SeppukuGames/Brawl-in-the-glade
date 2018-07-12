#ifndef __Scene2_h_
#define __Scene2_h_

#include "Scene.h"

class Scene2 : public Scene
{
public:
	Scene2();
	virtual void CreateScene(void);

protected:
	virtual void CreateLights(void);
	virtual void CreateCameras(void);
	virtual void CreateEntities(void);
};
#endif // #ifndef __Scene2_h_


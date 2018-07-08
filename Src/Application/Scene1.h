#ifndef __Scene1_h_
#define __Scene1_h_

#include "Scene.h"


class Scene1 : public Scene
{
	
public:
	Scene1();

protected:
	virtual void CreateScene(void); 
	virtual void CreateLights(void);
	virtual void CreateCameras(void);
	virtual void CreateEntities(void);
};
#endif // #ifndef __Scene1_h_


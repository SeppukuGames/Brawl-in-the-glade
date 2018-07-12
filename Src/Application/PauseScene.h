#ifndef __PauseScene_h_
#define __PauseScene_h_

#include "Scene.h"


class PauseScene : public Scene
{
private:

public:
	PauseScene();
	bool Tick(double elapsed);
	virtual void CreateScene(void);

protected:
	virtual void CreateCameras(void);
	virtual void CreateEntities(void);
	virtual void CreateLights(void);


private:
	void PauseAudio();
};
#endif // #ifndef __Scene1_h_


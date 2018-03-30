#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include "KeyInputObserver.h"
#include "BaseApplication.h"

class KeyInputComponent : public Component, public OIS::KeyListener{
public:

	//Seguramente haya que pasarle un puntero al GameManager
	KeyInputComponent(BaseApplication *app) : Component()
	{
		app->registerKeyInputObserver(this);
	};
	virtual ~KeyInputComponent(){};

private:
};

#endif /* RENDERCOMPONENT_H_ */
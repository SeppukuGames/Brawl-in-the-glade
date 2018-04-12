#ifndef KEYINPUTCOMPONENT_H_
#define KEYINPUTCOMPONENT_H_

#include "Component.h"
#include <OIS.h>

class KeyInputComponent : public Component, public OIS::KeyListener {
public:

	//Seguramente haya que pasarle un puntero al GameManager
	KeyInputComponent();
	
	virtual ~KeyInputComponent(){};

private:
};

#endif /* RENDERCOMPONENT_H_ */
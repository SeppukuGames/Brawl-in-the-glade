#ifndef KEYINPUTBSERVER_H_
#define KEYINPUTBSERVER_H_

#include "GameObject.h"
#include <OIS.h>

class KeyInputObserver {
public:
	KeyInputObserver(){};
	virtual ~KeyInputObserver(){};

	virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;
	virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;
};

#endif /* BALLOBSERVER_H_ */

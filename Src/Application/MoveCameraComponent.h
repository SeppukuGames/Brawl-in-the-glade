#ifndef MOVECAMERACOMPONENT_H_
#define MOVECAMERACOMPONENT_H_

#include "Component.h"
#include "MouseInputComponent.h"

using namespace Ogre;

class MoveCameraComponent : public MouseInputComponent
{
//--------------------------------ATRIBUTOS-----------------------------
private:

	Vector3 direction;
	float velocity;
	float rotation;
	RenderWindow* _mWindow;
	SceneManager* _mSceneMgr;
//--------------------------------ATRIBUTOS-----------------------------
//--------------------------------MÉTODOS-------------------------------
public:

	MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr);
	virtual ~MoveCameraComponent();

	virtual void start();
	virtual void tick(double elapsed);

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);

//--------------------------------MÉTODOS-------------------------------


};

#endif /* MOVECAMERACOMPONENT_H_ */
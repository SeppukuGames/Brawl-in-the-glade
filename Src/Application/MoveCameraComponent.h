#ifndef MOVECAMERACOMPONENT_H_
#define MOVECAMERACOMPONENT_H_

#include "DynamicRigidbodyComponent.h"
#include "KeyMouseInputComponent.h"

using namespace Ogre;

class MoveCameraComponent : public KeyMouseInputComponent
{

private:

	Vector3 direction;
	float velocity;
	float rotation;
	RenderWindow* _mWindow;
	SceneManager* _mSceneMgr;
	DynamicRigidbodyComponent* _rb;
	btVector3 pos;
	btTransform transform;
	GameObject* _player;
	
	//ESCALAS MOVIMIENTO DE CÁMARA
	const int mMoveScale = 30;
	const int mZoomScale = 15;
	const int maxZoomIn = -10;
	const int maxZoomOut = 10;
	int aumento = 0;
	int antiguoZoom = 0, actualZoom = 0;


public:
	
	MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr);
	virtual ~MoveCameraComponent();

	virtual void start();
	virtual void tick(double elapsed);

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);



	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	void MoveCameraComponent::setUpPlayer(GameObject* player);
};

#endif /* MOVECAMERACOMPONENT_H_ */
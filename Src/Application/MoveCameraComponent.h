#ifndef MOVECAMERACOMPONENT_H_
#define MOVECAMERACOMPONENT_H_

#include "MouseInputComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "KeyInputComponent.h"

using namespace Ogre;

//HEREDAR DE LOS DOS NO LO HAGAIS, SI NECESITAIS INPUT DE TECLADO, HACER OTRO COMPONENTE
class MoveCameraComponent : public MouseInputComponent//, public KeyInputComponent
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

public:
	MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr);
	virtual ~MoveCameraComponent();

	virtual void start();
	virtual void tick(double elapsed);

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);



	//virtual bool keyPressed(const OIS::KeyEvent &arg);
	//virtual bool keyReleased(const OIS::KeyEvent &arg);
	void MoveCameraComponent::setUpPlayer(GameObject* player);
};

#endif /* MOVECAMERACOMPONENT_H_ */
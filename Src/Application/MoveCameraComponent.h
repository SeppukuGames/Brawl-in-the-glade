#ifndef MOVECAMERACOMPONENT_H_
#define MOVECAMERACOMPONENT_H_

#include "Component.h"
#include "MouseInputComponent.h"

using namespace Ogre;


class MoveCameraComponent : public MouseInputComponent
{

public:

	MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr) : MouseInputComponent()
	{
		_mWindow = mWindow;
	}

	virtual ~MoveCameraComponent()
	{
	}

	virtual void start(){
		direction = Ogre::Vector3::ZERO;
	};
	
	virtual void tick(double elapsed){
		_gameObject->getNode()->translate(direction *Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
	};

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

		/*if (arg.state.buttonDown(OIS::MB_Right))
		{
		_gameObject->getNode()->yaw(Ogre::Degree(-rotation * arg.state.X.rel), Ogre::Node::TS_WORLD);
		_gameObject->getNode()->pitch(Ogre::Degree(-rotation * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
		}*/

		//int mMoveScale = -1;

		switch (id)
		{
		case OIS::MB_Middle:
			//direction.z += mMoveScale;
/*			_gameObject->getNode()->ca moveRelative(Vector3(0.0, 0.0, -0.1)
				* mInputDevice->getMouseRelativeZ() * MoveFactor);*/
			break;

		default:
			break;
		}


		/*
		Real MoveFactor = 60.0 * evt.timeSinceLastFrame;

		// Move the camera around with the left button
		if (mInputDevice->getMouseButton(1)) {
		SceneNode *camNode = mCamera->getParentSceneNode();

		if (camNode == 0) {
		std::cerr << "mCamera isn't attached to any SceneNode !" << std::endl;
		}

		camNode->yaw(Degree(mInputDevice->getMouseRelativeX() * MoveFactor * -0.1));
		camNode->pitch(Degree(mInputDevice->getMouseRelativeY() * MoveFactor * -0.1));
		}

		// Zoom with the middle button...
		if (mInputDevice->getMouseButton(2)) {
		mCamera->moveRelative(Vector3(0.0, 0.0, -0.5)
		* mInputDevice->getMouseRelativeY() * MoveFactor);
		}
		// ... and the wheel ;-)
		mCamera->moveRelative(Vector3(0.0, 0.0, -0.1)
		* mInputDevice->getMouseRelativeZ() * MoveFactor);
		*/

		return true;
	};


	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
	{
		return true;
	};

	virtual bool mouseMoved(const OIS::MouseEvent &arg)
	{
		//ROTACIÓN DE LA CÁMARA (Descomentar para probar)
		/*
		_gameObject->getNode()->yaw(Ogre::Degree(-rotation * arg.state.X.rel), Ogre::Node::TS_WORLD);
		_gameObject->getNode()->pitch(Ogre::Degree(-rotation * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
		*/
		int mMoveScale = 30;

		//X AXIS
		if (arg.state.X.abs > (_mWindow->getWidth() - 20) && arg.state.X.abs < _mWindow->getWidth())
		{
			direction.x += mMoveScale;
		}
		else if (arg.state.X.abs < (20) && arg.state.X.abs > 0)
			direction.x -= mMoveScale;
		else
			direction.x = 0;

		//Y AXIS
		if (arg.state.Y.abs >(_mWindow->getHeight() - 20) && arg.state.Y.abs < _mWindow->getHeight())
		{
			direction.z += mMoveScale;
		}
		else if (arg.state.Y.abs < (20) && arg.state.Y.abs > 0)
			direction.z -= mMoveScale;
		else
			direction.z = 0;

		return true;
	}


private:
	
	Vector3 direction;
	float velocity;
	float rotation;
	RenderWindow* _mWindow;
	SceneManager* _mSceneMgr;

};

#endif /* MOVECAMERACOMPONENT_H_ */
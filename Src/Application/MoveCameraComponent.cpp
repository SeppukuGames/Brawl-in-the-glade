#include "MoveCameraComponent.h"

MoveCameraComponent::MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr) : MouseInputComponent()
{
	_mWindow = mWindow;
}


MoveCameraComponent::~MoveCameraComponent()
{
}


void MoveCameraComponent::start()
{
	direction = Ogre::Vector3::ZERO;

}

void MoveCameraComponent::tick(double elapsed){
	_gameObject->getNode()->translate(direction *Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
}

bool MoveCameraComponent::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

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
}

bool MoveCameraComponent::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}

bool MoveCameraComponent::mouseMoved(const OIS::MouseEvent &arg)
{
	//ROTACI�N DE LA C�MARA (Descomentar para probar)
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
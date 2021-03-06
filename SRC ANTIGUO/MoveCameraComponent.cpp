
#include "MoveCameraComponent.h"
#include "GameObject.h"
#include <iostream>

MoveCameraComponent::MoveCameraComponent(RenderWindow* mWindow, SceneManager* mSceneMgr) : KeyMouseInputComponent()
{
	_mWindow = mWindow;
}


MoveCameraComponent::~MoveCameraComponent()
{
}


void MoveCameraComponent::start() {
	direction = Ogre::Vector3::ZERO;
};

void MoveCameraComponent::tick(double elapsed) {
	_gameObject->getNode()->translate(direction *Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);
};

bool MoveCameraComponent::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {

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
		direction.y += mMoveScale;
		direction.z += mMoveScale;
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


bool MoveCameraComponent::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	switch (id)
	{
	case OIS::MB_Middle:
		//direction.z += mMoveScale;
		/*			_gameObject->getNode()->ca moveRelative(Vector3(0.0, 0.0, -0.1)
		* mInputDevice->getMouseRelativeZ() * MoveFactor);*/
		direction.y = 0;
		direction.z = 0;
		break;

	default:
		break;
	}
	return true;
};

bool MoveCameraComponent::mouseMoved(const OIS::MouseEvent &arg)
{
	//ROTACI�N DE LA C�MARA (Descomentar para probar)
	/*
	_gameObject->getNode()->yaw(Ogre::Degree(-rotation * arg.state.X.rel), Ogre::Node::TS_WORLD);
	_gameObject->getNode()->pitch(Ogre::Degree(-rotation * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
	*/



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

	//ZOOM
	actualZoom = arg.state.Z.abs;

	if (actualZoom > antiguoZoom && aumento < maxZoomOut)		//AUMENTAR
		aumento++;
	else if (actualZoom < antiguoZoom && aumento > maxZoomIn)	//DISMINUIR
		aumento--;


	//std::cout << "Camera Z: " << arg.state.Z.abs << std::endl;


	if (aumento < maxZoomOut && actualZoom > antiguoZoom)
	{
		_gameObject->getNode()->setPosition(_gameObject->getNode()->getPosition().x, _gameObject->getNode()->getPosition().y + mZoomScale, _gameObject->getNode()->getPosition().z + mZoomScale);
		//direction.y += mZoomScale;
		//direction.z += mZoomScale;
	}
	else if (actualZoom < antiguoZoom && aumento > maxZoomIn) {
		_gameObject->getNode()->setPosition(_gameObject->getNode()->getPosition().x, _gameObject->getNode()->getPosition().y - mZoomScale, _gameObject->getNode()->getPosition().z - mZoomScale);
		//direction.y -= mZoomScale;
		//direction.z -= mZoomScale;
	}


	antiguoZoom = actualZoom;

	return true;
}

bool MoveCameraComponent::keyPressed(const OIS::KeyEvent &arg) {
	switch (arg.key)
	{
	case OIS::KC_SPACE:

		if (!game->getPauseStatus()) {
			_rb->getRigidbody()->getMotionState()->getWorldTransform(transform);
			//std::cout << "Transform X: " << transform.getOrigin().getX() << "\n Transform Z: " << transform.getOrigin().getZ() << std::endl;
			_gameObject->getNode()->setPosition(transform.getOrigin().getX(), 147, transform.getOrigin().getZ() + 300 + _camera->getPosition().z);
			//std::cout << "Camera X: " << _gameObject->getNode()->getPosition().x << "\n Camera Z: " << _gameObject->getNode()->getPosition().z << std::endl;
			aumento = 0;
		}
		break;

	default:
		break;
	}

	return true;
};

bool MoveCameraComponent::keyReleased(const OIS::KeyEvent &arg) {

	switch (arg.key)
	{
	case OIS::KC_SPACE:
		direction = Ogre::Vector3::ZERO;
		break;

	default:
		break;
	}
	return true;
};

void MoveCameraComponent::setUpPlayer(GameObject* player) {
	_player = player;
	_rb = dynamic_cast<DynamicRigidbodyComponent*> (_player->getComponent(ComponentName::RIGIDBODY));
}

void MoveCameraComponent::setUpCamera(Ogre::Camera* camera) {
	_camera = camera;
}

void MoveCameraComponent::setMainGameRef(MainGame* mainGame) {
	game = mainGame;
}
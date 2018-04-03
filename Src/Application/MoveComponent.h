#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "Component.h"
#include "KeyInputComponent.h"

using namespace Ogre;

class MoveComponent : public KeyInputComponent {
public:

	MoveComponent(RenderWindow* mWindow, SceneManager* mSceneMgr) : KeyInputComponent()
	{
		_mWindow = mWindow;
	};
	virtual ~MoveComponent(){};

	virtual void start(){
		velocity = 50;
		rotation = 0.13;
		direction = Ogre::Vector3::ZERO;
		transVector = Ogre::Vector3::ZERO;
	};
	virtual void tick(double elapsed){
		//_gameObject->getNode()->translate(direction * elapsed, Ogre::Node::TS_LOCAL);
		_gameObject->getNode()->translate(transVector* elapsed, Ogre::Node::TS_LOCAL);
	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.z = -velocity;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			direction.z = velocity;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			direction.x = -velocity;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			direction.x = velocity;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			direction.y = -velocity;
			break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
			direction.y = velocity;
			break;

		default:
			break;
		}
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){

		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.z = 0;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			direction.z = 0;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			direction.x = 0;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			direction.x = 0;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			direction.y = 0;
			break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
			direction.y = 0;
			break;

		default:
			break;
		}
		return true;
	};

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
		
		/*if (arg.state.buttonDown(OIS::MB_Right))
		{
			_gameObject->getNode()->yaw(Ogre::Degree(-rotation * arg.state.X.rel), Ogre::Node::TS_WORLD);
			_gameObject->getNode()->pitch(Ogre::Degree(-rotation * arg.state.Y.rel), Ogre::Node::TS_LOCAL);
		}*/
		int i = 0;

		switch (id)
		{
		case OIS::MB_Left:
			i++;
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
		int mMoveScale = 25;
		
		//X AXIS
		if (arg.state.X.abs > (_mWindow->getWidth() - 20))
		{
			transVector.x += mMoveScale;
		}
		else if (arg.state.X.abs < (20))
			transVector.x -= mMoveScale;
		else
			transVector.x = 0;

		//Y AXIS
		if (arg.state.Y.abs >(_mWindow->getHeight() - 20))
		{
			transVector.z += mMoveScale;
		}
		else if (arg.state.Y.abs < (20))
			transVector.z -= mMoveScale;
		else
			transVector.z = 0;

		//_mSceneMgr->getSceneNode("camNode")->translate(transVector, Ogre::Node::TS_LOCAL);
		return true;
	}



private:
	Ogre::Vector3 direction; 
	float velocity;
	float rotation;
	RenderWindow* _mWindow;
	SceneManager* _mSceneMgr;
	Vector3 transVector;
};

#endif /* MOVECOMPONENT_H_ */
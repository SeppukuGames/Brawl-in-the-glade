/*
-----------------------------------------------------------------------------
Filename:    MainGame.cpp
-----------------------------------------------------------------------------
This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

#include "TutorialBuffered.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
using namespace Ogre;

//-------------------------------------------------------------------------------------
TutorialBuffered::TutorialBuffered(void) : 
	mRotate(Ogre::Real(.13)),
	mMove(Ogre::Real(250)),
	mDirection(Ogre::Vector3::ZERO)
{
}
//-------------------------------------------------------------------------------------
TutorialBuffered::~TutorialBuffered(void)
{
}

//-------------------------------------------------------------------------------------

void TutorialBuffered::createLights(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.2f, .2f, .2f));

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);
}

//-------------------------------------------------------------------------------------

void TutorialBuffered::createCameras(void)
{
	//mCamera->setPosition(0, -370, 1000);

	  Ogre::SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  "CamNode1", Ogre::Vector3(1200, -370, 0));

	  node->yaw(Ogre::Degree(90));

	  mCamNode = node;
	  node->attachObject(mCamera);

	  node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  "CamNode2", Ogre::Vector3(-500, -370, 1000));
	  node->yaw(Ogre::Degree(-30));
}

//-------------------------------------------------------------------------------------

void TutorialBuffered::createEntities(void)
{
	Ogre::Entity* tudorEntity = mSceneMgr->createEntity("ogrehead.mesh"); //tudorhouse.mesh
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		"Node");
	node->attachObject(tudorEntity);
}

//-------------------------------------------------------------------------------------
void TutorialBuffered::createScene(void)
{
	// create your scene here :)

	createLights();

	createCameras();

	createEntities();
}
bool TutorialBuffered::update(void)
{

	mCamNode->translate(mDirection * mCamNode->getPosition(), Ogre::Node::TS_LOCAL);//ESTO NO SE HACE ASI, HAY QUE MULTIPLICAR MDIRECTION POR UN PARAMETRO DEL UPDATE

	return true;
}


bool TutorialBuffered::keyPressed(const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
	case OIS::KC_ESCAPE:
		//mShutDown = true;
		break;
	case OIS::KC_1:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
		break;

	case OIS::KC_2:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode2");
		mCamNode->attachObject(mCamera);
		break;

	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = -mMove;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = mMove;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = -mMove;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = mMove;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = -mMove;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = mMove;
		break;

	default:
		break;
	}

	return true;
}

bool TutorialBuffered::keyReleased(const OIS::KeyEvent& ke)
{
	switch (ke.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = 0;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = 0;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = 0;
		break;

	default:
		break;
	}
	return true;
}

bool TutorialBuffered::mouseMoved(const OIS::MouseEvent& me)
{
	if (me.state.buttonDown(OIS::MB_Right))
	{
		mCamNode->yaw(Ogre::Degree(-mRotate * me.state.X.rel), Ogre::Node::TS_WORLD);
		mCamNode->pitch(Ogre::Degree(-mRotate * me.state.Y.rel), Ogre::Node::TS_LOCAL);
	}
	return true;
}

bool TutorialBuffered::mousePressed(
	const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	Ogre::Light* light;
	switch (id)
	{
	case OIS::MB_Left:
		light = mSceneMgr->getLight("Light1");
		light->setVisible(!light->isVisible());
		break;

		default:
		break;
	}
	return true;
}

bool TutorialBuffered::mouseReleased(
	const OIS::MouseEvent& me, OIS::MouseButtonID id)
{

	return true;
}
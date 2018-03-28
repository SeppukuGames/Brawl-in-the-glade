#include "TutorialInt1.h"

TutorialInt1::TutorialInt1()
: mShutdown(false),
mDistance(0),
mWalkSpd(70.0),
mDirection(Ogre::Vector3::ZERO),
mDestination(Ogre::Vector3::ZERO),
mAnimationState(0),
mEntity(0),
mNode(0)
{
}

TutorialInt1::~TutorialInt1()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}


void TutorialInt1::createLights() {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
}

void TutorialInt1::createEntities() {
	mEntity = mSceneMgr->createEntity("robot.mesh");

	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		Ogre::Vector3(0, 0, 25.0));
	mNode->attachObject(mEntity);

	mWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mWalkList.push_back(Ogre::Vector3(-100.0, 0, -200.0));
	mWalkList.push_back(Ogre::Vector3(0, 0, 25.0));

	Ogre::Entity* ent;
	Ogre::SceneNode* node;

	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		Ogre::Vector3(0, -10.0, 25.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);

	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		Ogre::Vector3(550.0, -10.0, 50.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);

	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		Ogre::Vector3(-100.0, -10.0, -200.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
}

void TutorialInt1::createCameras() {
	mCamera->setPosition(90.0, 280.0, 535.0);
	mCamera->pitch(Ogre::Degree(-30.0));
	mCamera->yaw(Ogre::Degree(-15.0));
}

void TutorialInt1::createScene() {

	createLights();
	createEntities();
	createCameras();

	// Animacion
	mAnimationState = mEntity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
}


// Helper function for mouse events
/*CEGUI::MouseButton convertButton(OIS::MouseButtonID id)
{
	switch (id)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;
	case OIS::MB_Right:
		return CEGUI::RightButton;
	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
	default:
		return CEGUI::LeftButton;
	}
}
*/

/*bool TutorialInt1::setupCEGUI()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing CEGUI ***");

	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

	context.setDefaultFont("DejaVuSans-10");
	context.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	Ogre::LogManager::getSingletonPtr()->logMessage("Finished");

	return true;
}*/

#ifndef TutorialInt1_H
#define TutorialInt1_H

#include <OgreException.h>
#include <OgreEntity.h>

// #include <CEGUI/CEGUI.h>
// #include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "BaseApplication.h"

class TutorialInt1
	: public BaseApplication
{
public:
	TutorialInt1();
	virtual ~TutorialInt1();

protected:
	virtual void createScene(void);

	virtual void createLights(void);
	virtual void createCameras(void);
	virtual void createEntities(void);
private:

	bool mShutdown;

	// CEGUI
	// bool setupCEGUI();
	// CEGUI::OgreRenderer* mRenderer;

	//////////////////////
	// Tutorial Section //
	//////////////////////
	std::deque<Ogre::Vector3> mWalkList;

	Ogre::Real mDistance;
	Ogre::Real mWalkSpd;
	Ogre::Vector3 mDirection;
	Ogre::Vector3 mDestination;
	Ogre::AnimationState* mAnimationState;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mNode;
};

#endif


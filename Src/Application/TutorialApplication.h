#include <../Components/Terrain/include/OgreTerrain.h>
#include <../Components/Terrain/include/OgreTerrainGroup.h>

#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication();
	virtual ~TutorialApplication();

protected:
	virtual void createScene();
	virtual void destroyScene();

private:
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);

	bool mTerrainsImported;
	Ogre::TerrainGroup* mTerrainGroup;
	Ogre::TerrainGlobalOptions* mTerrainGlobals;

	

};
#ifndef __LightComponent_h_
#define __LightComponent_h_

#include "Component.h"
#include "GameObject.h"
#include <OgreEntity.h>

class LightComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Light * light;

#pragma endregion Attributes

#pragma region Methods  
public:
	LightComponent();

	virtual ~LightComponent();

	virtual void Start();

	inline Ogre::Light* GetLight(){ return light; }

#pragma endregion Methods

};

#endif /* __LightComponent_h_ */
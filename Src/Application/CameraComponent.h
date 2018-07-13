#ifndef __CameraComponent_h_
#define __CameraComponent_h_

#include "Component.h"
#include <Ogre.h>

class CameraComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Camera * camera;	//Referencia a la cámara

#pragma endregion Attributes

#pragma region Methods  
public:
	CameraComponent(Ogre::Camera * camera);

	virtual ~CameraComponent();

	virtual void Start();

	inline Ogre::Camera* GetCamera(){ return camera; }

#pragma endregion Methods

};

#endif /* __CameraComponent_h_ */
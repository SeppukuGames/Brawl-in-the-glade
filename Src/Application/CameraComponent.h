#ifndef __CameraComponent_h_
#define __CameraComponent_h_

#include <Ogre.h>

#include "Component.h"
#include "RigidbodyComponent.h"

class CameraComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Camera * camera;				//Referencia a la cámara
	RigidbodyComponent * rigidbody;
	float velocity;
	Ogre::Vector3 dir;
	Ogre::Vector3 initialPos;

#pragma endregion Attributes

#pragma region Methods  
public:
	CameraComponent();

	virtual ~CameraComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	inline Ogre::Camera* GetCamera(){ return camera; }

#pragma endregion Methods

};

#endif /* __CameraComponent_h_ */
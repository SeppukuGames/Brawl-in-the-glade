#ifndef __CameraComponent_h_
#define __CameraComponent_h_

#include <Ogre.h>

#include "Component.h"
#include "RigidbodyComponent.h"

class CameraComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Camera * camera;				//Referencia a la c�mara
	RigidbodyComponent * rigidbody;
	float velocity;
	Ogre::Vector3 dir;

#pragma endregion Attributes

#pragma region Methods  
public:
	CameraComponent(Ogre::Camera * camera);

	virtual ~CameraComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	inline Ogre::Camera* GetCamera(){ return camera; }

#pragma endregion Methods

};

#endif /* __CameraComponent_h_ */
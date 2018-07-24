#ifndef __CameraComponent_h_
#define __CameraComponent_h_

#include <Ogre.h>

#include "Component.h"
#include "RigidbodyComponent.h"
#include "InputManager.h"
#include "GraphicManager.h"

const float _VELOCITY = 15.f;

class CameraComponent : public Component{

#pragma region Attributes  
private:
	Ogre::Camera * camera;				//Referencia a la cámara
	RigidbodyComponent * rigidbody;
	Ogre::Vector3 dir;
	Ogre::Vector3 initialPos;

	//ESCALAS MOVIMIENTO DE CÁMARA
	const int mMoveScale = 30;
	const int mZoomScale = 15;
	const int maxZoomIn = -10;
	const int maxZoomOut = 10;
	int aumento = 0;
	int antiguoZoom = 0, actualZoom = 0;

#pragma endregion Attributes

#pragma region Methods  
public:
	CameraComponent();

	virtual ~CameraComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	inline Ogre::Camera* GetCamera(){ return camera; }

private:

	bool MouseMoved();
	void CheckZoom();
	void CheckBorders();
	void CheckReposition();
	MousePosition actualMousePos, oldMousePos;

#pragma endregion Methods

};

#endif /* __CameraComponent_h_ */
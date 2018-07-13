#include "CameraComponent.h"
#include "GameObject.h"

CameraComponent::CameraComponent(Ogre::Camera * camera) : Component(),camera (camera){
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start(){
	camera = gameObject->GetNode()->getCreator()->createCamera("Camera");
	gameObject->SetObjMan(camera);
}


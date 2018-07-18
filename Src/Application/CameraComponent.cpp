#include "CameraComponent.h"
#include "GameObject.h"
#include "InputManager.h"

CameraComponent::CameraComponent(Ogre::Camera * camera) : Component(),camera (camera){
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start(){
	rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));
	velocity.Set(0, 0);

	camera = gameObject->GetNode()->getCreator()->createCamera("Camera");
	gameObject->SetObjMan(camera);

	//rigidbody->GetBody()->SetTransform(b2Vec2(-10, 10), 0.0f);
	camera->setPosition(0, 0, 500);
}

void CameraComponent::Update(double elapsed) {

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_SPACE))
		rigidbody->GetBody()->SetTransform(velocity, -90.0f);

	//rigidbody->GetBody()->SetLinearVelocity(velocity);
}

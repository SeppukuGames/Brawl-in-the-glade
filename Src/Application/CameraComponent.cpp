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
	velocity = 5.0f;
	dir = (0, 0, 0);
	camera = gameObject->GetNode()->getCreator()->createCamera("Camera");
	gameObject->SetObjMan(camera);

	//rigidbody->GetBody()->SetTransform(b2Vec2(-10, 10), 0.0f);
	camera->setPosition(0, 550, -10);
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(-55.0f)), Ogre::Vector3(1, 0, 0));
	camera->rotate(quat);
	gameObject->GetNode()->setPosition(0, 0, 500);
}

void CameraComponent::Update(double elapsed) {

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_SPACE))
		dir.z += velocity;
	camera->move(dir *Ogre::Real(elapsed));
	
	//gameObject->GetNode()->translate(dir *Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

}

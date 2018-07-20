#include "CameraComponent.h"
#include "GameObject.h"
#include "InputManager.h"

CameraComponent::CameraComponent() : Component(){
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start(){
	
	//rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));
	velocity = 5.0f;
	dir = (0, 0, 0);
	initialPos = (0, 550, -10);

	camera = gameObject->GetNode()->getCreator()->createCamera("MainCamera");
	gameObject->SetObjMan(camera);

	//rigidbody->GetBody()->SetTransform(b2Vec2(-10, 10), 0.0f);
	camera->setPosition(0, 550, -10);
	Ogre::Quaternion quat;
	quat.FromAngleAxis(Ogre::Radian(Ogre::Degree(-55.0f)), Ogre::Vector3(1, 0, 0));
	camera->rotate(quat);
	gameObject->GetNode()->setPosition(0, 0, 500);
}

void CameraComponent::Update(double elapsed) {

	//Volver al principio
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_SPACE))
		camera->setPosition(initialPos);

	//ARREGLAR (Descubrir funcionamiento de input del ratón)
	/*if (Input::GetInstance()->getMousePosition() != ){
		//X AXIS
		if (arg.state.X.abs > (_mWindow->getWidth() - 20) && arg.state.X.abs < _mWindow->getWidth())
		{
			dir.x += velocity;
		}
		else if (arg.state.X.abs < (20) && arg.state.X.abs > 0)
			dir.x -= velocity;
		else
			dir.x = 0;

		//Y AXIS
		if (arg.state.Y.abs >(_mWindow->getHeight() - 20) && arg.state.Y.abs < _mWindow->getHeight())
		{
			dir.z += velocity;
		}
		else if (arg.state.Y.abs < (20) && arg.state.Y.abs > 0)
			dir.z -= velocity;
		else
			dir.z = 0;
	}*/

	camera->move(dir *Ogre::Real(elapsed));
	
	//gameObject->GetNode()->translate(dir *Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

}

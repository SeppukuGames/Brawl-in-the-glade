#include "CameraComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include <iostream>


CameraComponent::CameraComponent() : Component(){
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start(){
	
	//rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));
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

	actualMousePos = oldMousePos = Input::GetInstance()->getMousePosition();
}

void CameraComponent::Update(double elapsed) {

	//Reset camera to player's position
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_SPACE))
		CheckReposition();
	
	if (MouseMoved())
		CheckBorders();
	
	CheckZoom();

	camera->move(dir *Ogre::Real(elapsed));

}

bool CameraComponent::MouseMoved(){

	actualMousePos = Input::GetInstance()->getMousePosition();

	//Si se ha movido (coord. distintas)
	if (actualMousePos.X.abs != oldMousePos.X.abs || actualMousePos.Y.abs != oldMousePos.Y.abs){
		oldMousePos = actualMousePos;
		return true;
	}

	return false;
}

void CameraComponent::CheckZoom(){
	
	actualZoom = actualMousePos.Z.abs;

	if (actualZoom > antiguoZoom && aumento < maxZoomOut)		//AUMENTAR
		aumento++;
	else if (actualZoom < antiguoZoom && aumento > maxZoomIn)	//DISMINUIR
		aumento--;

	if (aumento < maxZoomOut && actualZoom > antiguoZoom)
	{
		camera->setPosition(camera->getPosition().x, camera->getPosition().y + mZoomScale, camera->getPosition().z + mZoomScale);
		//_gameObject->getNode()->setPosition(_gameObject->getNode()->getPosition().x, _gameObject->getNode()->getPosition().y + mZoomScale, _gameObject->getNode()->getPosition().z + mZoomScale);
	}
	else if (actualZoom < antiguoZoom && aumento > maxZoomIn) {
		camera->setPosition(camera->getPosition().x, camera->getPosition().y - mZoomScale, camera->getPosition().z - mZoomScale);
		//_gameObject->getNode()->setPosition(_gameObject->getNode()->getPosition().x, _gameObject->getNode()->getPosition().y - mZoomScale, _gameObject->getNode()->getPosition().z - mZoomScale);
	}

	antiguoZoom = actualZoom;
}

void CameraComponent::CheckBorders(){
	
	Ogre::RenderWindow *_mWindow = GraphicManager::GetInstance()->GetWindow();

	//X AXIS
	if (actualMousePos.X.abs > (_mWindow->getWidth() - 20) && actualMousePos.X.abs < _mWindow->getWidth())
	{
		dir.x += _VELOCITY;
	}
	else if (actualMousePos.X.abs < (20) && actualMousePos.X.abs > 0)
		dir.x -= _VELOCITY;
	else
		dir.x = 0;

	//Y AXIS
	if (actualMousePos.Y.abs >(_mWindow->getHeight() - 20) && actualMousePos.Y.abs < _mWindow->getHeight())
	{
		dir.z += _VELOCITY;
	}
	else if (actualMousePos.Y.abs < (20) && actualMousePos.Y.abs > 0)
		dir.z -= _VELOCITY;
	else
		dir.z = 0;
}

void CameraComponent::CheckReposition(){
	
	GameObject* player = SceneManager::GetInstance()->GetCurrentScene()->GetPlayer();
	Ogre::Vector3 newPos = camera->getPosition();
	newPos.x = ((RigidbodyComponent*)player->GetComponent(ComponentName::RIGIDBODY))->GetBody()->GetPosition().x;
	newPos.z = ((RigidbodyComponent*)player->GetComponent(ComponentName::RIGIDBODY))->GetBody()->GetPosition().y;
	aumento = 0;
	camera->setPosition(newPos);
}
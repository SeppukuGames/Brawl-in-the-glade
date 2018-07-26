#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Error.h"
#include <Box2D.h>
#include <iostream>
#include "GameManager.h"
#include "AnimationComponent.h"
#include "SceneManager.h"
#include "GraphicManager.h"
#include <math.h>

#define M_PI acos(-1.0)

PlayerComponent::PlayerComponent() : rigidbody(nullptr)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start(){

	rigidbody = (RigidbodyComponent*)(gameObject->GetComponent(RIGIDBODY));
	velocity.Set(0, 0);
	angle = 0.0f;
	isMoving = false;

	if (rigidbody == nullptr){
		Error errorE("\n\n\n\n\nError al crear el PlayerComponent. Necesita un Rigidbody ");
		throw errorE;
	}

	gameObject->AddComponent(new AnimationComponent("Idle2"));	//Le pasas una inicial, luego la cambias desde el input
	//rigidbody->GetBody()->SetAngularVelocity(-10.0f);
	
}

void PlayerComponent::Update(double elapsed){
	
	if (CheckMovement(elapsed) && !isMoving){
		((AnimationComponent*)gameObject->GetComponent(ComponentName::ANIMATION))->blend("Walk",
			((AnimationComponent*)gameObject->GetComponent(ComponentName::ANIMATION))->BlendWhileAnimating, Ogre::Real(0.3), true);

		isMoving = true;
	}
	else if(!CheckMovement(elapsed) && isMoving) {
		((AnimationComponent*)gameObject->GetComponent(ComponentName::ANIMATION))->blend("Idle2",
			((AnimationComponent*)gameObject->GetComponent(ComponentName::ANIMATION))->BlendWhileAnimating, Ogre::Real(0.3), true);
		isMoving = false;
	}
		
	

	CheckRotation(elapsed);
	
	velocity.x *= elapsed;
	velocity.y *= elapsed;

	rigidbody->GetBody()->SetLinearVelocity(velocity);
	//rigidbody->GetBody()->SetAngularVelocity(angle);

	//Acceso a la instancia de GameManager
	GameManager::GetInstance()->GetGameObject()->GetNode()->getName();

}

void PlayerComponent::OnCollisionEnter(ColliderComponent* collider){
	std::cout << "Entra en con Colisión con" + collider->GetGameObject()->GetNode()->getName() + '\n';
}

void PlayerComponent::OnCollisionExit(ColliderComponent* collider){
	std::cout << "Sale de la Colisión con" + collider->GetGameObject()->GetNode()->getName() + '\n';
}

bool PlayerComponent::CheckMovement(double elapsed){
	
	bool hasMoved = false;

	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_S)){
			velocity.y += _LINEARVELOCITY;
			hasMoved = true;
	}

		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_W)){
			velocity.y -= _LINEARVELOCITY;
			hasMoved = true;
		}

		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_D)){
			velocity.x += _LINEARVELOCITY;
			hasMoved = true;
		}

		if (Input::GetInstance()->getKey(OIS::KeyCode::KC_A)){
			velocity.x -= _LINEARVELOCITY;
			hasMoved = true;
		}

		return hasMoved;
}

void PlayerComponent::CheckRotation(double elapsed){
	
	if (Input::GetInstance()->getKey(OIS::KeyCode::KC_Q))
		angle = -_ANGULARVELOCITY;

	/*float bodyAngle = rigidbody->GetBody()->GetAngle();
	MousePosition mousePos = Input::GetInstance()->getMousePosition();
	b2Vec2 mouseCoord(mousePos.X.abs, mousePos.Y.abs);
	b2Vec2 toTarget = mouseCoord - rigidbody->GetBody()->GetPosition();
	float desiredAngle = atan2f(-toTarget.x, toTarget.y);
	desiredAngle *= (180 / M_PI);*/

	/*std::cout << mousePos.X.abs << "\n";
	if (desiredAngle < 0)
		desiredAngle = 360 - (-desiredAngle);
	*/

	
	/*float totalRotation = desiredAngle - bodyAngle;

	while (totalRotation < -180) totalRotation += 360;
	while (totalRotation >  180 ) totalRotation -= 360;
	
	totalRotation *= (180 / M_PI);
	*/
	//totalRotation *= 5;
	//rigidbody->GetBody()->SetAngularVelocity(0);
	//rigidbody->GetBody()->SetTransform(rigidbody->GetBody()->GetPosition(), -90 + desiredAngle);
	
	//rigidbody->GetBody()->SetTransform(rigidbody->GetBody()->GetPosition(), totalRotation);
	
	Ogre::Plane mPlane(Ogre::Vector3::UNIT_Y, 0);

	// get window height and width
	Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
	Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

	MousePosition mousePos = Input::GetInstance()->getMousePosition();
	b2Vec2 mouseCoord(mousePos.X.abs, mousePos.Y.abs);
	
	// convert to 0-1 offset
	Ogre::Real offsetX = mouseCoord.x / GraphicManager::GetInstance()->GetWindow()->getWidth();
	Ogre::Real offsetY = mouseCoord.y / GraphicManager::GetInstance()->GetWindow()->getWidth();

	// set up the ray
	Ogre::Ray mouseRay = SceneManager::GetInstance()->GetCurrentScene()->GetCamera()->getCameraToViewportRay(offsetX, offsetY);

	// check if the ray intersects our plane
	// intersects() will return whether it intersects or not (the bool value) and
	// what distance (the Real value) along the ray the intersection is
	std::pair<bool, Ogre::Real> result = mouseRay.intersects(mPlane);

	if (result.first) {
		// if the ray intersect the plane, we have a distance value
		// telling us how far from the ray origin the intersection occurred.
		// the last thing we need is the point of the intersection.
		// Ray provides us getPoint() function which returns a point
		// along the ray, supplying it with a distance value.

		// get the point where the intersection is
		Ogre::Vector3 resultado = mouseRay.getPoint(result.second);
		//std::cout << resultado.y << std::endl;

		b2Vec2 newMouseCoord(resultado.x, resultado.z);
		b2Vec2 toTarget = newMouseCoord - rigidbody->GetBody()->GetPosition();
		float desiredAngle = atan2f(toTarget.y, toTarget.x);
		
		desiredAngle *= (180 / M_PI);

		//while (totalRotation < -180) totalRotation += 360;
		//while (totalRotation >  180) totalRotation -= 360;
		
		/*if (desiredAngle < 0)
			desiredAngle = 360 - (-desiredAngle);*/

		std::cout << desiredAngle << std::endl;
		
		rigidbody->GetBody()->SetAngularVelocity(0);
		rigidbody->GetBody()->SetTransform(rigidbody->GetBody()->GetPosition(), desiredAngle);
	}


}


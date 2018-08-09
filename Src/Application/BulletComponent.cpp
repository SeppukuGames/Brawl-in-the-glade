#include "BulletComponent.h"

#include "SceneManager.h"
#include "StatsComponent.h"
#include "PlayerComponent.h"
#include "GraphicManager.h"
#include "InputManager.h"
#include <math.h>
#include <iostream>



BulletComponent::BulletComponent() : Component()
{


}


BulletComponent::~BulletComponent()
{
}

void BulletComponent::Start(){
	cont = .0;

	rb = (RigidbodyComponent*)gameObject->GetComponent(ComponentName::RIGIDBODY);
	rb->GetBody()->SetBullet(true);
	DireccionarBala();
}

void BulletComponent::Update(double elapsed){
	cont += elapsed;

	//std::cout << "Angulo personaje: " << rb->GetBody()->GetAngle() << '\n';

	if (cont > bulletDuration)
		DestruyeBala();

	else{

		b2Vec2 newVec(direccion.x, direccion.y);
		newVec *= 10;
		newVec -= rb->GetBody()->GetPosition();

		newVec *= velocidad;

		newVec *= elapsed;
		rb->GetBody()->SetLinearVelocity(newVec);
	}
}

void BulletComponent::OnCollisionEnter(ColliderComponent* collider){

	//std::cout << "Colision con " + collider->GetGameObject()->GetNode()->getName() + '\n';
	if (collider->GetGameObject()->GetTag() == "Enemy"){
		StatsComponent* stats = (StatsComponent*)collider->GetGameObject()->GetComponent(ComponentName::STATS);
		StatsComponent* player_stats = (StatsComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->GetComponent(ComponentName::STATS);
		stats->HitGameObject(player_stats->GetAttackPower());	//CAMBIAR
	}

	//MIRAR POR QUÉ FALLA
	if (collider->GetGameObject()->GetTag() != "Player")
		DestruyeBala();

}

void BulletComponent::DireccionarBala(){

	/*RigidbodyComponent* player_rb = (RigidbodyComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->GetComponent(ComponentName::RIGIDBODY);
	b2Vec2 pos = player_rb->GetBody()->GetPosition();
	pos.x += 5;
	pos.y += 5;
	//float angl = rb->GetBody()->GetAngle() * M_PI / 180.f;
	rb->GetBody()->SetTransform(pos, player_rb->GetBody()->GetAngle());
	//direccion.x = cos(rb->GetBody()->GetAngle());
	//direccion.y = sin(rb->GetBody()->GetAngle());

	direccion.x = cos(rb->GetBody()->GetAngle());
	direccion.y = sin(rb->GetBody()->GetAngle());*/

	RigidbodyComponent* player_rb = (RigidbodyComponent*)SceneManager::GetInstance()->GetCurrentScene()->GetPlayer()->GetComponent(ComponentName::RIGIDBODY);
	b2Vec2 pos = player_rb->GetBody()->GetPosition();
	rb->GetBody()->SetTransform(pos, player_rb->GetBody()->GetAngle());

	Ogre::Plane mPlane(Ogre::Vector3::UNIT_Y, 0);

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
		direccion = newMouseCoord - rb->GetBody()->GetPosition();
	}


}
void BulletComponent::DestruyeBala(){
	SceneManager::GetInstance()->GetCurrentScene()->Destroy(gameObject);
}


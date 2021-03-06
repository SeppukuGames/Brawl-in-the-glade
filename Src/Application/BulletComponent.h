#ifndef BULLETCOMPONENT_H_
#define BULLETCOMPONENT_H_

#include "Component.h"
#include "RigidbodyComponent.h"

class BulletComponent : public Component {

private:
	
	 
	const float bulletDuration = 5.0f;		//Duracion de la bala en el juego	
	const float velocidad = 15000000.0f;

	float cont;
	
	//FISICA
	RigidbodyComponent *rb;
	b2Vec2 direccion;
	float rot;


	void OnCollisionEnter(ColliderComponent* collider);

public:

	BulletComponent();
	virtual ~BulletComponent();

	void Start();
	void Update(double elapsed);
	void DireccionarBala();
	bool BulletComponent::RaycastFromPoint(Ogre::Real posMouseX, Ogre::Real posMouseY,
		Ogre::Vector3 &result);
	//virtual void onCollision(GameObject *collision);

	void DestruyeBala();
};
#endif
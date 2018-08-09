#ifndef __PlayerComponent_h_
#define __PlayerComponent_h_

#include "Component.h"
#include "RigidbodyComponent.h"

const float _LINEARVELOCITY = 5000.f;
const float _ANGULARVELOCITY = 150.f;

class PlayerComponent : public Component{

#pragma region Attributes  
private:
	RigidbodyComponent * rigidbody;
	b2Vec2 velocity;
	float angle;
	bool isMoving;

	bool clickFlag;		//Flag para controlar que no se pulse más de una vez tras un click
	const float refreshRate = .3f;
	float cont;
#pragma endregion Attributes

#pragma region Methods  

public:
	PlayerComponent();
	virtual ~PlayerComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	virtual void OnCollisionEnter(ColliderComponent* collider);		//Es llamado cuando dos gameObject colisionan.
	virtual void OnCollisionExit(ColliderComponent* collider);		//Es llamado cuando dos gameObject dejan de colisionar. 

private:
	bool CheckMovement(double elapsed);
	void CheckRotation(double elapsed);
	void Attack();
	bool PlayerComponent::RaycastFromPoint(Ogre::Real posMouseX, Ogre::Real posMouseY,
		Ogre::Vector3 &result);
	void PlayerComponent::GetMeshInformation(const Ogre::MeshPtr mesh,
		size_t &vertex_count,
		Ogre::Vector3* &vertices,
		size_t &index_count,
		unsigned long* &indices,
		const Ogre::Vector3 &position,
		const Ogre::Quaternion &orient,
		const Ogre::Vector3 &scale);

#pragma endregion Methods

};

#endif /* __PlayerComponent_h_ */
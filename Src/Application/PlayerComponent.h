#ifndef __PlayerComponent_h_
#define __PlayerComponent_h_

#include "Component.h"
#include "RigidbodyComponent.h"

class PlayerComponent : public Component{

#pragma region Attributes  
private:
	RigidbodyComponent * rigidbody;

#pragma endregion Attributes

#pragma region Methods  

public:
	PlayerComponent();
	virtual ~PlayerComponent();

	virtual void Start();
	virtual void Update(double elapsed);

	virtual void OnCollisionEnter(ColliderComponent* collider);		//Es llamado cuando dos gameObject colisionan.
	virtual void OnCollisionExit(ColliderComponent* collider);		//Es llamado cuando dos gameObject dejan de colisionar. 

#pragma endregion Methods

};

#endif /* __PlayerComponent_h_ */
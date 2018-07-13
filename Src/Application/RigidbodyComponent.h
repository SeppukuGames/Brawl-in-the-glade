#ifndef __RigidbodyComponent_h_
#define __RigidbodyComponent_h_

#include "Box2D.h"
#include "ColliderComponent.h"

class RigidbodyComponent : public Component{

#pragma region Attributes  
private:
	float density;			//Atributo para establecer la densidad del objeto
	bool kinematic;			//Booleana para establecer si el objeto es kinemático o no
	b2Body *body;			//Referencia al body de CollisionComponent

#pragma endregion Attributes

#pragma region Methods  

public:
	RigidbodyComponent(bool kinematic = false, float density = DEFAULTDENSITY);
	virtual ~RigidbodyComponent();

	virtual void Start();

	virtual void Update(double elapsed);			//Método que controla la posición y orientación del objeto en cada frame
	
	inline b2Body * GetBody(){ return body; };		//Método para obtener el body del objeto

private:
#pragma endregion Methods

};

#endif /* __RigidbodyComponent_h_ */
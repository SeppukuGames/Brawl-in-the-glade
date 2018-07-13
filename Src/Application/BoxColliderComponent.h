#ifndef __BoxColliderComponent_h_
#define __BoxColliderComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class BoxColliderComponent : public ColliderComponent{

#pragma region Attributes  
private:
	float w, h; //Atributos para la altura y la anchura del collider

#pragma endregion Attributes

#pragma region Methods  

public:
	BoxColliderComponent(float w, float h, PhysicsMaterial material = PhysicsMaterial());
	virtual ~BoxColliderComponent();

private:

	virtual b2Shape* CreateShape();				//3. Método que construye la forma del objeto (Cubo en este caso)


#pragma endregion Methods

};

#endif /* __BoxColliderComponent_h_ */
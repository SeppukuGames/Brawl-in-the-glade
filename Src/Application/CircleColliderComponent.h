#ifndef __CircleColliderComponent_h_
#define __CircleColliderComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class CircleColliderComponent : public ColliderComponent{

#pragma region Attributes  
private:
	float radius; //Atributo para guardar el radio del círculo

#pragma endregion Attributes

#pragma region Methods  

public:
	CircleColliderComponent(float radius, PhysicsMaterial material = PhysicsMaterial());
	virtual ~CircleColliderComponent();

private:

	virtual b2Shape* CreateShape();				//3. Método que construye la forma del objeto (Círculo en este caso)


#pragma endregion Methods

};

#endif /* __CircleColliderComponent_h_ */
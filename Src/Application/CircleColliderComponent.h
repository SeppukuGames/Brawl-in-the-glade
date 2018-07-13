#ifndef __CircleColliderComponent_h_
#define __CircleColliderComponent_h_

#include "ColliderComponent.h"
#include "Box2D.h"

class CircleColliderComponent : public ColliderComponent{

#pragma region Attributes  
private:
	float radius; //Atributo para guardar el radio del c�rculo

#pragma endregion Attributes

#pragma region Methods  

public:
	CircleColliderComponent(float radius, PhysicsMaterial material = PhysicsMaterial());
	virtual ~CircleColliderComponent();

private:

	virtual b2Shape* CreateShape();				//3. M�todo que construye la forma del objeto (C�rculo en este caso)


#pragma endregion Methods

};

#endif /* __CircleColliderComponent_h_ */
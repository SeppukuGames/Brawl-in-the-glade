#ifndef TOWERCOMPONENT_H_
#define TOWERCOMPONENT_H_

#include "Component.h"
class TowerComponent : public Component
{

private:
	const float BaseHeal = 10.0f;									//Curacion base
	float healingScale;												//Añadido que tiene la torre para modificar la curación base

public:
	TowerComponent();
	~TowerComponent();

	//From Component.h
	void Start();
	void Update(double elapsed);

	//Estaría cool que emitiera un sonido cuando fuera atacado
	virtual void OnCollisionEnter(ColliderComponent* collider){};		//Es llamado cuando dos gameObject colisionan.
	virtual void OnCollisionExit(ColliderComponent* collider){};		//Es llamado cuando dos gameObject dejan de colisionar. 

	//Self methods
	void healUp();
	void reestablishTowerGUI();
};

#endif

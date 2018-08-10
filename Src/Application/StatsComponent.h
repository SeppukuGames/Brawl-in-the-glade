#ifndef STATSCOMPONENT_H_
#define STATSCOMPONENT_H_

#include "Component.h"
#include "RigidbodyComponent.h"

class StatsComponent : public Component{

#pragma region Attributes  
private:
	float life;
	float maxLife;
	float attackPower;

#pragma endregion Attributes

#pragma region Methods  

public:

	StatsComponent::StatsComponent() : Component(){};
	virtual ~StatsComponent(){};

	virtual void Start();

	float GetLife() { return life; };
	float GetMaxLife() { return maxLife; };
	float GetAttackPower() { return attackPower; };

	void HitGameObject(float amount);
	void SetEnemyWave(RigidbodyComponent* rb);

#pragma endregion Methods

};

#endif 
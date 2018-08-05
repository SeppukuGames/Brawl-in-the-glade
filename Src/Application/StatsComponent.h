#ifndef STATSCOMPONENT_H_
#define STATSCOMPONENT_H_

#include "Component.h"
#include "CanvasComponent.h"
#include "GameObject.h"

class StatsComponent : public Component{

#pragma region Attributes  
private:
	float life;
	float maxLife;
	float attackPower;

#pragma endregion Attributes

#pragma region Methods  

public:

StatsComponent::StatsComponent() : Component(){
	life = maxLife = 100;
	attackPower = 5;
};
virtual ~StatsComponent(){};

	float GetLife() { return life; };
	float GetMaxLife() { return maxLife; };
	float GetAttackPower() { return attackPower; };

	void HitGameObject(float amount)
	{ 
		life -= amount; 
		CanvasComponent* canvas = (CanvasComponent*)gameObject->GetComponent(ComponentName::CANVAS);
		canvas->HitGameObject(amount);
	};

#pragma endregion Methods

};

#endif 
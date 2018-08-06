#ifndef STATSCOMPONENT_H_
#define STATSCOMPONENT_H_

#include "Component.h"
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
	attackPower = 50;
};
virtual ~StatsComponent(){};

	float GetLife() { return life; };
	float GetMaxLife() { return maxLife; };
	float GetAttackPower() { return attackPower; };

	void HitGameObject(float amount){ life -= amount; };
	void SetPosition(Ogre::Vector3 posicion){ gameObject->GetNode()->setPosition(posicion); };
	void SetLife(float vida){ life = vida; }
	void SetMaxLife(float vida){ maxLife = vida; }
	

#pragma endregion Methods

};

#endif 
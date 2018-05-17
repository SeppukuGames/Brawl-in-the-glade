#ifndef PLAYERCOMPONENT_H_
#define PLAYERCOMPONENT_H_

//#include "GameComponent.h"
#include "Component.h"

class PlayerComponent : public Component
{

private:

	//PLAYER STATS
	float life;
	float maxLife;
	float attackPower;

public:

	PlayerComponent(float newLife, float newAttackPower) : Component()
	{
		life = maxLife = newLife;
		attackPower = newAttackPower;
	}

	virtual ~PlayerComponent()
	{
	}

	virtual void start() {

	};

	virtual void tick(double elapsed) {
	};

	float getCurrentLife() {
		return life;
	}

	float getMaxLife() {
		return maxLife;
	}

	float getAttackPower() {
		return attackPower;
	}

	void hitPlayer(float amount) {
		life -= amount;
	}
};

#endif

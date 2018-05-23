#ifndef PLAYERCOMPONENT_H_
#define PLAYERCOMPONENT_H_

//#include "GameComponent.h"
#include "Component.h"
#include <iostream>

class PlayerComponent : public Component
{

private:

	//PLAYER STATS
	float life;
	const float maxLife = 1.f;
	const float attackPower = 100.f;

	UICanvas* playerUI;
	MainGame* game;
	float maxWidth, maxHeight;

public:

	PlayerComponent() : Component()
	{
		life = maxLife;
	}

	virtual ~PlayerComponent()
	{
	}

	virtual void start() {

	};

	virtual void tick(double elapsed) {
		//std::cout << "Tick player!" << std::endl;
		if (life <= 0) {
			game->ShowGameOver();
		}
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
		setNewUISize((maxWidth * life) / maxLife, maxHeight);
		updateUI();
	}

	//UI METHODS

	void setNewUISize(float x, float y) {
		playerUI->setNewUISize(x, y);
	}

	float getUIWidth() {
		return maxWidth;
	}

	float getUIHeigth() {
		return maxHeight;
	}
	void updateUI() {
		playerUI->updateUI();
	}

	//SETTERS
	void setPlayerUI() {
		playerUI = dynamic_cast<UICanvas*> (_gameObject->getComponent(ComponentName::UI));
		maxWidth = playerUI->getUIWidth();
		maxHeight = playerUI->getUIHeight();
		updateUI();
	}

	void setMainGameRef(MainGame* mainGame) {
		game = mainGame;
	}
};

#endif

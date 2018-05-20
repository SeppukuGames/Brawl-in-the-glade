#ifndef TOWERCOMPONENT_H_
#define TOWERCOMPONENT_H_

//#include "GameComponent.h"
#include "Component.h"
#include "DynamicRigidbodyComponent.h"
#include <cmath> 
#include <iostream>

class TowerComponent : public Component {
public:

	TowerComponent() : Component()
	{
		life = maxLife;
	};

	virtual ~TowerComponent() {};

	virtual void start() {
	};


	virtual void tick(double elapsed) {

	};

	void setTowerUI() {
		towerUI = dynamic_cast<UICanvas*> (_gameObject->getComponent(ComponentName::UI));
		maxWidth = towerUI->getUIWidth();
		maxHeight = towerUI->getUIHeight();
		updateUI();
	}

	void updateUI() {
		towerUI->updateUI();
	}

	void hitTower(float amount) {
		life -= amount;
		std::cout << "Tower Life: " << life << std::endl;
		//setNewUISize((maxWidth * life) / maxLife, maxHeight);
		//updateUI();
	}

private:

	//Atributos de la torre
	float life;								//La vida de la torre en cada momento
	const float maxLife = 10000.f;			//La vida máxima de la torre
	//const float attackPower = 50;			//El poder de ataque de la torre

	UICanvas* towerUI;
	float maxWidth, maxHeight;

};

#endif /* TOWERCOMPONENT */
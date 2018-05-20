#ifndef TOWERCOMPONENT_H_
#define TOWERCOMPONENT_H_

//#include "GameComponent.h"
#include "Component.h"
#include "DynamicRigidbodyComponent.h"
#include <cmath> 
#include <iostream>
#include <OgreBillboardSet.h>

class TowerComponent : public Component {

private:

	//Atributos de la torre
	float life;								//La vida de la torre en cada momento
	const float maxLife = 10000.f;			//La vida máxima de la torre
											//const float attackPower = 50;			//El poder de ataque de la torre

	BillboardSet* towerUI;
	float maxWidth, maxHeight;


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

	void setTowerUI(BillboardSet* newBillboard) {
		towerUI = newBillboard;
		maxWidth = towerUI->getDefaultWidth();
		maxHeight = towerUI->getDefaultHeight();
	}

	void hitTower(float amount) {
		life -= amount;
		//std::cout << "Tower Life: " << life << std::endl;
		towerUI->setDefaultDimensions((maxWidth * life) / maxLife, maxHeight);
	}



};

#endif /* TOWERCOMPONENT */
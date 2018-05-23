#ifndef ENEMIGO2_H_
#define ENEMIGO2_H_

#include "Enemigo.h"

class Enemigo2 : public Enemigo {

public:

	Enemigo2() : Enemigo()	{};

	virtual ~Enemigo2(){};

	virtual void start(){
		Enemigo::start();
		velocity = 0.08f;
		int max = maxLife*2;		
		life = max;		
	};


	//virtual void tick(double elapsed);

	//float obtenerDistancia();
	
	//void obtenerDireccion();	

	//void Fire() {	}

	//void setUpPlayer(GameObject* player) {	}

	//void setUpTower(GameObject* tower) {	}

	//void setEnemyUI(BillboardSet* newBillboard) {	}

	//void hitEmemy(float amount) {	}

};

#endif /* ENEMYCOMPONENT */
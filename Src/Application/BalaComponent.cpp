
#include "BalaComponent.h"
#include "MainGame.h"
#include "Enemigo.h"


void BalaComponent::start(){
	vida = 15;
	velocidad = 2000;

	//Mete el impulso inicial
	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));


	Direccion.normalize();
	std::cout << "Direccion X:" << Direccion.getX() << "Direccion Y:" << Direccion.getZ() << std::endl;
	rb->getRigidbody()->applyCentralImpulse(Direccion * velocidad);
	//
	//rb->getRigidbody()->getMotionState()->setWorldTransform(transform);

}

void BalaComponent::tick(double elapsed){
	if (vida > 0){

		vida--;
	}

	else{
		DestruyeBala();
	}
}

void BalaComponent::onCollision(GameObject *collision)
{
	if (collision != nullptr)
	{

		std::cout << "Colision con " + collision->getNode()->getName() + '\n';

		//Detectamos de que tipo es la colisión de esta manera
		Enemigo* Ogro = dynamic_cast<Enemigo*> (collision->getComponent(ComponentName::ENEMY));
		if (Ogro != nullptr)
		{
			Ogro->hitEmemy(10);
			DestruyeBala();
		}

	}
	else
		std::cout << "Colision con objeto estático" + '\n';
}


void BalaComponent::DestruyeBala(){
	MainGame::getInstance()->DestroyGameObject(_gameObject);
}
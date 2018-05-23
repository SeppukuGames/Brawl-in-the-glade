
#include "BalaComponent.h"
#include "MainGame.h"
#include "Enemigo.h"


void BalaComponent::start(){
	vida = 1000;
	velocidad = 20;

	//Mete el impulso inicial
	rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
	////Las colisiones hulio
	//std::cout << rb->getRigidbody()->getActivationState() << std::endl;

	//transform = rb->getRigidbody()->getWorldTransform();
	//
	////Aplicas la fuerza
	//transform.setRotation(rotacion);
	//rb->getRigidbody()->setLinearVelocity(Direccion *  velocidad);
	if (Direccion.length() < 5) {
		velocidad *= 10;
	}
	std::cout << "Direccion X:" << Direccion.getX() << "Direccion Y:" << Direccion.getZ() << std::endl;
	rb->getRigidbody()->applyCentralImpulse(Direccion * velocidad);
	//
	//rb->getRigidbody()->getMotionState()->setWorldTransform(transform);

}

void BalaComponent::tick(double elapsed){
	if (vida > 0){


		vida--;
	}

	//Si vida = 0, se para.
}

void  BalaComponent::onCollision(GameObject *collision)
{
	if (collision != nullptr)
	{

		std::cout << "Colision con " + collision->getNode()->getName() + '\n';

		//Detectamos de que tipo es la colisión de esta manera
		Enemigo* Ogro = dynamic_cast<Enemigo*> (collision->getComponent(ComponentName::ENEMY));
		if (Ogro != nullptr)
		{
			Ogro->hitEmemy(200);
			DestruyeBala();
		}

	}
	else
		std::cout << "Colision con objeto estático" + '\n';
}


void BalaComponent::DestruyeBala(){
	MainGame::getInstance()->DestroyGameObject(_gameObject);
}
#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_



//using namespace Ogre;  Va a dar errores por esto.s

#include "Component.h"
#include "KeyInputComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "MouseComponent.h"
#include "RigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
#include <stdlib.h>
#include <math.h>       /* acos */
#include <iostream>


#define PI 3.14159265

class MoveComponent : public KeyInputComponent, public Component {
public:

	MoveComponent() : KeyInputComponent(), Component()
	{
		
	};
	virtual ~MoveComponent(){};

	virtual void start(){
		velocity = 500;
		animComp =  dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
        mouseComponent = dynamic_cast<MouseComponent*> (_gameObject->getComponent(ComponentName::MOUSE));
		direction = { 0, 0, 0 };	
		mouseOldPos = mouseComponent->getMousePos();
		oldDirection = direction;
	};

	virtual void tick(double elapsed){

		if (oldDirection != direction) {
			rb->getRigidbody()->setLinearVelocity(direction * 10 * Ogre::Real(elapsed));
			oldDirection = direction;
		}
		//btTransform transform;
		//rb->getRigidbody()->getMotionState()->getWorldTransform(transform);
		//_gameObject->getNode()->translate(direction* Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

		//PARA ROTAR EL PERSONAJE
		std::cout << "------------------------------------------" << std::endl;
		Vector3 mousePos = mouseComponent->getMousePos();
		
       
        Vector3 ninjaPos = _gameObject->getNode()->getPosition();
		

        // Construir un vector de direccion apuntando desde el centro del personaje hacia la posicion donde queremos que mire.
		// Vector3 vectorDirector = Vector3(-1, 0, 0);
		Vector3 vectorDirector = Vector3(0, 1, 0);
		// Vector3 vectorDirector = Vector3(0, 0, -1);

        // Multiplicamos el vector por el quaternion para obtener el vector comienzo
        Quaternion aux = _gameObject->getNode()->getOrientation();
		Vector3 vectorComienzo = aux * vectorDirector;
		

        // Restamos la posicion del raton en coordenadas globales desde el centro del personaje para obtener el vector final
		btVector3 centroDeMasa = rb->getRigidbody()->getCenterOfMassPosition();
		Vector3 centerOfMass = Vector3(centroDeMasa.m_floats[0], centroDeMasa.m_floats[1], centroDeMasa.m_floats[2]);
		Vector3 vectorFinal = mousePos - centerOfMass;
		

        // Obtenemos el producto vectorial de los dos anteriores (el orden importa, comienzo * final es lo que queremos) para obtener el eje de rotacion
		vectorComienzo.normalise();
		vectorFinal.normalise();
		Vector3 crossProduct = vectorComienzo;
        crossProduct.crossProduct(vectorFinal);
		

        // Obtenemos el producto escalar del comienzo y el final (ambos deben estar normalizados) para obtener el coseno del angulo de rotacion.
        // Usamos el arcocoseno en el para obtener el angulo ENTRE DOS.
        Real dotProduct = vectorComienzo.dotProduct(vectorFinal);
        dotProduct = asin(dotProduct) * 180.0 / PI;
		
		std::cout << "Prcuto vectorial: " << crossProduct << std::endl;
		//if (){ }
	

		//Los valores actuales pasan a ser los antiguos
		if (crossProduct != Vector3(0, 0, 0)) {
			//	if (mousePos.x < mouseOldPos.x)
			if (crossProduct.x < 0)
				rb->getRigidbody()->setAngularVelocity(btVector3(0, crossProduct.y * dotProduct * Ogre::Real(elapsed), 0));
			else if (crossProduct.x > 0)
				rb->getRigidbody()->setAngularVelocity(btVector3(0, (-1) * crossProduct.y * dotProduct * Ogre::Real(elapsed), 0));
			else 
				rb->getRigidbody()->setAngularVelocity(btVector3(0, 0, 0));

			//	else if (mousePos.x > mouseOldPos.x){
			//		rb->getRigidbody()->setAngularVelocity(btVector3(0, (-1) * crossProduct.y * dotProduct, 0));
			//
			//	mouseOldPos = mousePos;
			//}
		}
        
		
		std::cout << "------------------------------------------" << std::endl;
	}

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.setZ((-velocity));
			//direction.z += -velocity;
		
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:

			direction.setZ((velocity));
			//direction.z += velocity;
			
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:

			//direction.x += -velocity;
			direction.setX((-velocity));
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:

			//direction.x += velocity;
			direction.setX((velocity));
			break;
		}

		//E ORA DO MOVIMENTO
		animComp->blend("Walk", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
		return true;
	};

	virtual bool keyReleased(const OIS::KeyEvent &arg){

		switch (arg.key)
		{
		case OIS::KC_UP:

		case OIS::KC_W: 
			//direction.z += velocity;
			direction.setZ((0));
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:

			//direction.z += -velocity;
			direction.setZ((0));
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:

			//direction.x += velocity;
			direction.setX((0));
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:

			//direction.x += -velocity;
			direction.setX((0));

			break;
		}
		animComp->blend("Idle2", animComp->BlendWhileAnimating, Ogre::Real(0.2), true);
		return true;
	};


	

private:
	Vector3 mouseOldPos;
	
	//Ogre::Vector3 direction; 
	float velocity;
	btVector3 direction, oldDirection;
	DynamicRigidbodyComponent* rb;
    MouseComponent * mouseComponent;
	//Puntero a la animacion
	AnimationComponent* animComp;
};

#endif /* MOVECOMPONENT_H_ */
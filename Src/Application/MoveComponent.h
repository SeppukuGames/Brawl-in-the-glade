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


	bool isOnLine(Ogre::Real x, Ogre::Real y, Ogre::Real x1, Ogre::Real y1, Ogre::Real x2, Ogre::Real y2){
		//if (x >= x1 && x <= x2 && (y >= y1 && y <= y2 || y <= y1 && y >= y2)) {
		//	Ogre::Real vx = x2 - x1;
		//	Ogre::Real vy = y2 - y1;
		//	Ogre::Real mag = sqrt(vx*vx + vy*vy);
		//	// need to get the unit vector (direction)
		//	float dvx = vx / mag; // this would be the unit vector (direction) x for the line
		//	float dvy = vy / mag; // this would be the unit vector (direction) y for the line
		//
		//	Ogre::Real vcx = x - x1;
		//	Ogre::Real vcy = y - y1;
		//	Ogre::Real magc = sqrt(vcx*vcx + vcy*vcy);
		//	// need to get the unit vector (direction)
		//	Ogre::Real dvcx = vcx / magc; // this would be the unit vector (direction) x for the point
		//	Ogre::Real dvcy = vcy / magc; // this would be the unit vector (direction) y for the point
		//
		//	// I was thinking of comparing the direction of the two vectors, if they are the same then the point must lie on the line?
		//	return (vx * vcy == vy * vcx);  // might still need a tolerance for floating-point
		//}
		Vector2 p1 = Vector2(x, y);
		Vector2 p2 = Vector2(x1, y1);
		Vector2 p3 = Vector2(x2, y2);


		Vector2 prEscalarOld = p2;
		prEscalarOld.crossProduct(p3);
		Vector2 prEscalarNew = p2;
		prEscalarNew.crossProduct(p1);

		//if ()
	}

	virtual void start(){
		velocity = 500;
		animComp = dynamic_cast<AnimationComponent*> (_gameObject->getComponent(ComponentName::ANIMATION));
		rb = dynamic_cast<DynamicRigidbodyComponent*> (_gameObject->getComponent(ComponentName::RIGIDBODY));
		mouseComponent = dynamic_cast<MouseComponent*> (_gameObject->getComponent(ComponentName::MOUSE));
		direction = { 0, 0, 0 };
		mouseOldPos = mouseComponent->getMousePos();
	};

	virtual void tick(double elapsed){

		rb->getRigidbody()->setLinearVelocity(direction * 10 * Ogre::Real(elapsed));
		//btTransform transform;
		//rb->getRigidbody()->getMotionState()->getWorldTransform(transform);
		//_gameObject->getNode()->translate(direction* Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

		//PARA ROTAR EL PERSONAJE
		/*Quaternion q = Quaternion(0.7, 0.7, 0.7, 0);
		_gameObject->getNode()->setOrientation(q);*/
		Vector3 mousePos = mouseComponent->getMousePos();
		_gameObject->getNode()->lookAt(Vector3(mousePos.x, _gameObject->getNode()->getPosition().y, mousePos.y), Ogre::Node::TransformSpace::TS_WORLD);
		//std::cout << "Producto vectorial " << Vector3(mousePos.x, 0, mousePos.y) << std::endl;


		Vector3 ninjaPos = _gameObject->getNode()->getPosition();

		{
			// Construir un vector de direccion apuntando desde el centro del personaje hacia la posicion donde queremos que mire.
			//Vector3 vectorDirector = Vector3(1, 0, 0);
			//Vector3 vectorDirector = Vector3(0, 1, 0);
			Vector3 vectorDirector = Vector3(0, 0, -1);

			// Multiplicamos el vector por el quaternion para obtener el vector comienzo
			Quaternion aux = _gameObject->getNode()->getOrientation();
			Vector3 playerOrientation = aux * Vector3(1, 1, 1);
			aux.y = 1;
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

			/*
			Do: Aplicar la velocidad angular
			While: Una línea recta dese la orientacion del ninja NO contenga al punto
			*/
			//std::cout << "Producto vectorial " << crossProduct << std::endl;

			//if (!isOnLine(mousePos.x, mousePos.z, playerOrientation.x, playerOrientation.z, mouseOldPos.x, mouseOldPos.z)){
			if (playerOrientation.x > mousePos.x) {
				rb->getRigidbody()->applyTorque(btVector3(0, crossProduct.y * dotProduct * 2, 0));
			}

			else if (playerOrientation.x < mousePos.x){
				rb->getRigidbody()->applyTorque(btVector3(0, (-1) * crossProduct.y * dotProduct * 2, 0));
			}

			//}

			rb->getRigidbody()->setAngularVelocity(btVector3(0, 0, 0));
		}

		// btQuaternion currentOrientation = rb->getRigidbody()->getOrientation();
		// btQuaternion targetOrientation = currentOrientation;
		// float x = mousePos.x;
		// float z = mousePos.z;
		// targetOrientation.setX(x);
		// targetOrientation.setZ(z);
		// 
		// btQuaternion deltaOrientation = targetOrientation *  currentOrientation.inverse();
		// btVector3 deltaEuler = btVector3(0,0,0);
		// deltaOrientation.getEulerZYX(deltaEuler.m_floats[2], deltaEuler.m_floats[1], deltaEuler.m_floats[0]);
		// 
		// Vector3 pollasEnVinagre = Vector3(deltaEuler.m_floats[0], deltaEuler.m_floats[1], deltaEuler.m_floats[2]);
		// 
		// std::cout << pollasEnVinagre << std::endl;
		// rb->getRigidbody()->applyTorque(deltaEuler * 20);

	}

	virtual bool keyPressed(const OIS::KeyEvent &arg){
		const Vector3 zero(Ogre::Real(0), Ogre::Real(0), Ogre::Real(0));
		Quaternion q = zero.getRotationTo(Vector3(Ogre::Real(0), Ogre::Real(0), Ogre::Real(0)));

		switch (arg.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			direction.setZ((-velocity));
			//direction.z += -velocity;
			//Vector3(0.0,0).
			//_gameObject->getNode()->setOrientation(q);

			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:

			direction.setZ((velocity));
			//direction.z += velocity;
			//_gameObject->getNode()->setOrientation(Vector3(0, 180, 0).getRotationTo(Vector3(0, 0, 0)));

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
	btVector3 direction;
	DynamicRigidbodyComponent* rb;
	MouseComponent * mouseComponent;
	//Puntero a la animacion
	AnimationComponent* animComp;
};

#endif /* MOVECOMPONENT_H_ */

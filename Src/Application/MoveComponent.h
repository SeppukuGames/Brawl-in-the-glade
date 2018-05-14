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
		oldDirection = direction;
	};

	virtual void tick(double elapsed){

		if (oldDirection != direction) {
			rb->getRigidbody()->setLinearVelocity(direction * 10 * Ogre::Real(elapsed));
			oldDirection = direction;
		}
		btTransform transform;
		rb->getRigidbody()->getMotionState()->getWorldTransform(transform);
		//_gameObject->getNode()->translate(direction* Ogre::Real(elapsed), Ogre::Node::TS_LOCAL);

		//PARA ROTAR EL PERSONAJE
        Vector3 mousePos = mouseComponent->getMousePos();
       
        Vector3 ninjaPos = _gameObject->getNode()->getPosition();

        // Construir un vector de direccion apuntando desde el centro del personaje hacia la posicion donde queremos que mire.
        Vector3 vectorDirector = ninjaPos - mousePos;

        // Multiplicamos el vector por el quaternion para obtener el vector comienzo
        Quaternion aux = _gameObject->getNode()->getOrientation();
        Ogre::Real tuputamadre = aux.getYaw().valueDegrees();
        Vector3 vectorComienzo = Vector3(vectorDirector.x, vectorDirector.y * tuputamadre, vectorDirector.z);

        // Restamos la posicion del raton en coordenadas globales desde el centro del personaje para obtener el vector final
        Vector3 vectorFinal = Vector3(abs(mousePos.x - vectorComienzo.x), vectorComienzo.y, abs(mousePos.y - vectorComienzo.z));

        // Obtenemos el producto vectorial de los dos anteriores (el orden importa, comienzo * final es lo que queremos) para obtener el eje de rotacion
        Vector3 crossProduct = vectorComienzo;
        crossProduct.crossProduct(vectorFinal);

        // Obtenemos el producto escalar del comienzo y el final (ambos deben estar normalizados) para obtener el coseno del angulo de rotacion.
        // Usamos el arcocoseno en el para obtener el angulo ENTRE DOS.
        vectorComienzo.normalise();
        vectorFinal.normalise();
        Real dotProduct = vectorComienzo.dotProduct(vectorFinal);
        dotProduct = acos(dotProduct) * 180.0 / PI;

        //if (!a){
            rb->getRigidbody()->applyTorque(btVector3(0, dotProduct/2, 0));
        //a = true;
        //}
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
    bool a =  false;
	//Ogre::Vector3 direction; 
	float velocity;
	btVector3 direction, oldDirection;
	DynamicRigidbodyComponent* rb;
    MouseComponent * mouseComponent;
	//Puntero a la animacion
	AnimationComponent* animComp;
};

#endif /* MOVECOMPONENT_H_ */
#ifndef MOUSECOMPONENT_H_
#define MOUSECOMPONENT_H_

#include "Component.h"
#include "MouseInputComponent.h"
#include "Factory.h"
#include "GameObject.h"
#include <iostream>

using namespace Ogre;


class MouseComponent : public MouseInputComponent
{

public:

	MouseComponent(Ogre::Camera * cam, Ogre::AxisAlignedBox * pl) : MouseInputComponent()
	{
		Cam = cam;
		//"Awake"
		plano = (*pl);
	}

	virtual ~MouseComponent()
	{
	}

	virtual void start(){
		
	};
	
	virtual void tick(double elapsed){
		
	};

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
		//Click izquierdo: Dispara la bala.
		Viewport * vp = _gameObject->getNode()->getCreator()->getCurrentViewport();
		posMouseX = arg.state.X.abs / Real(vp->getActualWidth());;
		posMouseY = arg.state.Y.abs / Real(vp->getActualHeight());;
		std::cout << "x: " << posMouseX << " y: " << posMouseY << std::endl;

		if (id == OIS::MB_Left){
			//Dispara una bala.
			
			dirBala = _gameObject->getNode()->getOrientation(); //Devuelve un quaternion
			BulletFactory::creaBala(_gameObject->getNode()->getCreator(), dirBala, _gameObject->getNode()->getPosition());
		}

		return true;
	}


	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
		return true;
	};


	//Cada vez que movemos el ratón vamos guardando sus coodenadas
	virtual bool mouseMoved(const OIS::MouseEvent &arg)
	{
		// get window height and width
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		// convert to 0-1 offset
		posMouseX = arg.state.X.abs / screenWidth;
		posMouseY = arg.state.Y.abs / screenHeight;
       
		//http://wiki.ogre3d.org/Get+XZ+coordinates
		Ray mouseRay = Cam->getCameraToViewportRay(posMouseX, posMouseY);

		std::pair<bool, Real> result = mouseRay.intersects(plano);

		//Si result. first == true significa que estás en el plano, y entonces quieres actualizar posición
		//El plano no es puntero porque no se va a modificar, pero coge la referencia
		if (result.first){
			// get the point where the intersection is
			resultado = mouseRay.getPoint(result.second);
		}

		return true;
	}

    Vector3 getMousePos(){
		
        return resultado;
    }
	
private:
	int posMouseX, posMouseY;
	Ogre::Quaternion dirBala;

	Vector3 resultado;
	Ogre::Camera * Cam;
	Ogre::AxisAlignedBox plano;

};

#endif /* MOVECAMERACOMPONENT_H_ */
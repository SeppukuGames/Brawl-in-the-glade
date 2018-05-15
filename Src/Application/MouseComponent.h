#ifndef MOUSECOMPONENT_H_
#define MOUSECOMPONENT_H_

#include "Component.h"
#include "MouseInputComponent.h"
#include "Factory.h"
#include <iostream>

using namespace Ogre;


class MouseComponent : public MouseInputComponent
{

public:

	MouseComponent() : MouseInputComponent()
	{
		
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
        posMouseX = arg.state.X.abs;
        posMouseY = arg.state.Y.abs;

		return true;
	}

    Vector3 getMousePos(){
		
        return Vector3(posMouseX, 0, posMouseY);
    }
	
private:
	int posMouseX, posMouseY;
	Ogre::Quaternion dirBala;

};

#endif /* MOVECAMERACOMPONENT_H_ */
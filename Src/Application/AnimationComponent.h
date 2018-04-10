#ifndef __AnimationComponent_h_
#define __AnimationComponent_h_

#include "Component.h"
//#include "KeyInputComponent.h"
#include "EntityComponent.h"	//Hereda de EntityComponent porque normalmente querremos animar meshes

#include <map>


enum AnimationID{
	ANIM_IDLE1, ANIM_ATTACK1, ANIM_BACKFLIP, ANIM_DEATH1, ANIM_SPIN
};

class AnimationComponent : public Component {
public:

	AnimationComponent(std::string animName)
	{
		baseAnim = animName;
		
	};
	virtual ~AnimationComponent() {};

	virtual void start() {
		
		//Variables
		mDistance = 0;
		mWalkSpd = 70.0;

		//Vectores
		mDirection = Ogre::Vector3::ZERO;
		mDestination = Ogre::Vector3::ZERO;


		//El mesh que vamos a animar
		animEntity = dynamic_cast<EntityComponent*> (_gameObject->getComponent(ComponentName::ENTITY))->getEntity();
		setAnimation(baseAnim, true);
	};
	virtual void tick(double elapsed) {
		//aqui va lo de pasar de frame de animación :D
	
		animacionActual -> addTime((Ogre::Real)elapsed);

		//Si no hay, poner de nuevo la de idle?

	};
	

	//Cambia la animación
	void setAnimation(std::string newAnim, bool looped) {
		//get animation

		animacionActual = animEntity->getAnimationState(newAnim);
		
		animacionActual->setLoop(looped);
		animacionActual->setEnabled(true);

		//animStack.push_back(nuevoAnimState);

	}

	

private:
	//Comunicación directa con el componente de mesh
	EntityComponent* entityComponent;

	//Elementos de Animación
	std::string baseAnim;
	Ogre::AnimationState* animacionActual;
	Ogre::Entity* animEntity;					//Entidad que almacena la animación

	//Pila de animaciones
	std::list <Ogre::AnimationState*> animStack;

	//Elementos del tutorial 
	Ogre::Real mDistance;
	Ogre::Real mWalkSpd;
	Ogre::Vector3 mDirection;
	Ogre::Vector3 mDestination;
	
	float velocity;
};



#endif // !1


#ifndef __AnimationComponent_h_
#define __AnimationComponent_h_

#include "Component.h"
//#include "KeyInputComponent.h"
#include "EntityComponent.h"	//Hereda de EntityComponent porque normalmente querremos animar meshes
#include <stack>

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

		//TEST//
		mWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
		mWalkList.push_back(Ogre::Vector3(-100.0, 0, -200.0));
		mWalkList.push_back(Ogre::Vector3(0, 0, 25.0));

		//El mesh que vamos a animar
		animEntity = dynamic_cast<EntityComponent*> (_gameObject->getComponent(ComponentName::ENTITY))->getEntity();
		stackIdle(baseAnim);
	};
	virtual void tick(double elapsed) {
		//aqui va lo de pasar de frame de animación :D
	
		mAnimationState->addTime((Ogre::Real)elapsed);

	};

	void stackIdle(std::string animName) {

		//get animation
		mAnimationState = animEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);

		animStack.push(mAnimationState);
	}

	

	//Cambia la animación
	void stackAnimation(std::string newAnim) {
		//get animation
		mAnimationState = animEntity->getAnimationState(newAnim);
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);


	}

private:
	//Comunicación directa con el componente de mesh
	EntityComponent* entityComponent;

	//Elementos de Animación
	std::string baseAnim;
	Ogre::AnimationState* mAnimationState;		//Estados de la animación
	Ogre::Entity* animEntity;					//Entidad que almacena la animación

	//Pila de animaciones
	std::stack <Ogre::AnimationState*> animStack;

	//Elementos del tutorial 
	Ogre::Real mDistance;
	Ogre::Real mWalkSpd;
	Ogre::Vector3 mDirection;
	Ogre::Vector3 mDestination;
	
	float velocity;

	//Se usa para establecer una cola de waypoints (Seguramente vaya en la IA en verdad)
	std::deque<Ogre::Vector3> mWalkList;
};



#endif // !1


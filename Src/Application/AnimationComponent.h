#ifndef __AnimationComponent_h_
#define __AnimationComponent_h_

#include "Component.h"
//#include "KeyInputComponent.h"
#include "EntityComponent.h"	//Hereda de EntityComponent porque normalmente querremos animar meshes

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
		createAnimation(baseAnim);
	};
	virtual void tick(double elapsed) {
		//aqui va lo de pasar de frame de animaci�n :D
	
		mAnimationState->addTime((Ogre::Real)elapsed);

		

	};

	void createAnimation(std::string animName) {

		//get animation
		mAnimationState = animEntity->getAnimationState(animName);
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}

	//A�ade waypoints a la rutina 
	void queueAnimationPosition(){
	
	}

	//Cambia la animaci�n
	void changeCurrentAnimation(std::string newAnim) {

	}

private:
	//Comunicaci�n directa con el componente de mesh
	EntityComponent* entityComponent;

	//Elementos de Animaci�n
	std::string baseAnim;
	Ogre::AnimationState* mAnimationState;		//Estados de la animaci�n
	Ogre::Entity* animEntity;					//Entidad que almacena la animaci�n


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


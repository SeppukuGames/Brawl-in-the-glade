#ifndef __AnimationComponent_h_
#define __AnimationComponent_h_

#include "Component.h"
#include <Ogre.h>
//#include "EntityComponent.h"	//Hereda de EntityComponent porque normalmente querremos animar meshes
#include <map>

class AnimationComponent : public Component {
public:
	//------------------------------------ENUMERADOS------------------------------------------
	enum AnimationID{
		ANIM_IDLE1, ANIM_ATTACK1, ANIM_BACKFLIP, ANIM_DEATH1, ANIM_SPIN
	};

	enum BlendingTransition
	{
		BlendWhileAnimating,   // cross fade, blend source animation out while blending destination animation in
		BlendThenAnimate      // blend source to first frame of dest, when done, start dest anim
	};
	//------------------------------------ENUMERADOS------------------------------------------


	//----------------------------------------ATRIBUTOS---------------------------------------

private:
	//Comunicaci�n directa con el componente de mesh
//	EntityComponent* entityComponent;

	//Elementos de Animaci�n
	std::string baseAnim;
	Ogre::AnimationState* animacionActual;			//mSource
	Ogre::AnimationState* animacionSiguiente = 0;	//mTarget
	Ogre::Entity* animEntity;						//Entidad que almacena la animaci�n

	Ogre::Real mTimeleft = 0;
	Ogre::Real mDuration = 1;
	bool complete = false;

	//Blending transition 
	BlendingTransition mTransition;

	bool loop;
	//----------------------------------------ATRIBUTOS---------------------------------------

	//-------------------------------------M�TODOS--------------------------------------------

public:

	AnimationComponent(std::string animName);
	virtual ~AnimationComponent();

	virtual void Start();
	virtual void Update(double elapsed);
	
	//Cambia la animaci�n
	void setAnimation(std::string newAnim, bool looped);

	void blend(const std::string &animation, BlendingTransition transition, Ogre::Real duration, bool l);
		
	//GETS DEL ANIMATION STATE:
	inline Ogre::AnimationState *getSource() { return animacionActual; }
	inline Ogre::AnimationState *getTarget() { return animacionSiguiente; }
};

//-------------------------------------M�TODOS--------------------------------------------


#endif /* ANIMATIONCOMPONENT_H_ */


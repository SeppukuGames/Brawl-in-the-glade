#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(std::string animName)
{
	baseAnim = animName;
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::start()
{
	//El mesh que vamos a animar
	animEntity = dynamic_cast<EntityComponent*> (_gameObject->getComponent(ComponentName::ENTITY))->getEntity();

	setAnimation(baseAnim, true);
}

void AnimationComponent::tick(double elapsed){

	//aqui va lo de pasar de frame de animación :D

	//animacionActual -> addTime((Ogre::Real)elapsed);
	//Check this out
	if (animacionActual != 0)
	{
		if (mTimeleft > 0)
		{
			mTimeleft -= (Ogre::Real)elapsed;
			if (mTimeleft <= 0)
			{
				// finish blending
				animacionActual->setEnabled(false);
				animacionActual->setWeight(0);
				animacionActual = animacionSiguiente;
				animacionActual->setEnabled(true);
				animacionActual->setWeight(1);
				animacionSiguiente = 0;
			}
			else
			{
				// still blending, advance weights
				animacionActual->setWeight(mTimeleft / mDuration);
				animacionSiguiente->setWeight(Ogre::Real(1.0 - mTimeleft / mDuration));
				if (mTransition == BlendingTransition::BlendWhileAnimating)
					animacionSiguiente->addTime((Ogre::Real)elapsed);
			}
		}
		if (animacionActual->getTimePosition() >= animacionActual->getLength())
		{
			complete = true;
		}
		else
		{
			complete = false;
		}
		animacionActual->addTime((Ogre::Real)elapsed);
		animacionActual->setLoop(loop);
	}


}

void AnimationComponent::setAnimation(std::string newAnim, bool looped) {
	//get animation

	animacionActual = animEntity->getAnimationState(newAnim);

	animacionActual->setLoop(looped);
	animacionActual->setEnabled(true);

	//animStack.push_back(nuevoAnimState);

}

void AnimationComponent::blend(const std::string &animation, BlendingTransition transition, Ogre::Real duration, bool l){
	loop = l;

	Ogre::AnimationState *nuevaAnim = animEntity->getAnimationState(animation);

	if (mTimeleft > 0)
	{
		// oops, weren't finished yet
		if (nuevaAnim == animacionSiguiente)
		{
			// nothing to do! (ignoring duration here)
		}
		else if (nuevaAnim == animacionActual)
		{
			// going back to the source state, so let's switch
			animacionActual = animacionSiguiente;
			animacionSiguiente = nuevaAnim;
			mTimeleft = mDuration - mTimeleft; // i'm ignoring the new duration here
		}
		else
		{
			// ok, nuevaAnim is really new, so either we simply replace the target with this one, or
			// we make the target the new source
			if (mTimeleft < mDuration * 0.5)
			{
				// simply replace the target with this one
				animacionSiguiente->setEnabled(false);
				animacionSiguiente->setWeight(0);
			}
			else
			{
				// old target becomes new source
				animacionActual->setEnabled(false);
				animacionActual->setWeight(0);
				animacionActual = animacionSiguiente;

			}
			animacionSiguiente = nuevaAnim;
			animacionSiguiente->setEnabled(true);
			animacionSiguiente->setWeight(Ogre::Real(1.0 - mTimeleft / mDuration));
			animacionSiguiente->setTimePosition(0);
		}
	}
	else
	{
		// assert( target == 0, "target should be 0 when not blending" )
		// mSource->setEnabled(true);
		// mSource->setWeight(1);
		mTransition = transition;
		mTimeleft = mDuration = duration;
		animacionSiguiente = nuevaAnim;
		animacionSiguiente->setEnabled(true);
		animacionSiguiente->setWeight(0);
		animacionSiguiente->setTimePosition(0);
	}
}
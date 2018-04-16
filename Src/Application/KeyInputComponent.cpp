#include "KeyInputComponent.h" 
#include "TutorialApplication.h"
//BORRAR EL CPP
KeyInputComponent::KeyInputComponent() : Component()
{
	TutorialApplication::getInstance()->registerKeyInputObserver(this);
}



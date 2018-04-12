#include "KeyInputComponent.h" 
#include "TutorialApplication.h"

KeyInputComponent::KeyInputComponent() : Component()
{
	TutorialApplication::getInstance()->registerKeyInputObserver(this);
}



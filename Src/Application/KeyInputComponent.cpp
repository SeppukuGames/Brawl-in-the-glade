#include "KeyInputComponent.h" //Queda arreglar el MoveComponent
#include "TutorialApplication.h"

KeyInputComponent::KeyInputComponent() : Component()
{
	TutorialApplication::getInstance()->registerKeyInputObserver(this);
}



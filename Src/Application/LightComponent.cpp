#include "LightComponent.h"
#include "GameObject.h"

LightComponent::LightComponent() : Component(){
}

LightComponent::~LightComponent()
{
	gameObject->GetNode()->detachObject(light);
	gameObject->GetNode()->getCreator()->destroyLight(light);
}

void LightComponent::Start(){
	light = gameObject->GetNode()->getCreator()->createLight();
	gameObject->SetObjMan(light);
}


#include "LightComponent.h"
#include "GameObject.h"

LightComponent::LightComponent() : Component(){
}

LightComponent::~LightComponent()
{
	delete light;
}

void LightComponent::Start(){
	light = gameObject->GetNode()->getCreator()->createLight();
	gameObject->SetObjMan(light);
}


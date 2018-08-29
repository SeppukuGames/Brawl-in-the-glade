#include "TowerComponent.h"
#include "StatsComponent.h"
#include "SceneManager.h"


TowerComponent::TowerComponent()
{
}


TowerComponent::~TowerComponent()
{
}

void TowerComponent::Start(){
	healingScale = 1;
}

void TowerComponent::Update(double elapsed){
	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);

	//If estas muerto
	if (stats->isDead()){
		PrefabManager::GetInstance()->resetNameInts();
		SceneManager::GetInstance()->LoadScene(GAMEOVERSCENE);
	}
}

//La idea de este componente es que al pasar de rondas más complicadas
//Se cure una cantidad de vida a la torre, y aumente ese factor
void TowerComponent::healUp(){

	StatsComponent* stats = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);
	stats->SetLife(stats->GetLife() + (healingScale * BaseHeal));

	healingScale++;

}
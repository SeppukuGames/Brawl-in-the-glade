#include "PhysicsManager.h"

#pragma region Singleton  
/* Null, because instance will be initialized on demand. */
PhysicsManager* PhysicsManager::instance = 0;

PhysicsManager* PhysicsManager::GetInstance()
{
	if (instance == 0)
		instance = new PhysicsManager();

	return instance;
}

void PhysicsManager::ResetInstance(){
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton

PhysicsManager::PhysicsManager() :world(0)
{
}

PhysicsManager::~PhysicsManager()
{
	delete world;
	world = nullptr;
}

void PhysicsManager::InitPhysics()
{
	b2Vec2 gravity(0,GRAVITY);
	world = new b2World(gravity); 	//Inicializar el mundo
}

void PhysicsManager::Tick()
{
	//Avanzar el mundo
	world->Step(TIMESTEP, VELOCITYITERATIONS, POSITIONITERATIONS);
}

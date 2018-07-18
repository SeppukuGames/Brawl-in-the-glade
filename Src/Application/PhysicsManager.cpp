#include "PhysicsManager.h"
#include "GameObject.h"

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

//M�todo encargado de inicializar la f�sica
void PhysicsManager::InitPhysics()
{
	b2Vec2 gravity(0, GRAVITY);
	world = new b2World(gravity); 	//Inicializar el mundo
	//Nos suscribimos a las funciones de beginContact
	world->SetContactListener(this);
}

//M�todo que actualiza el estado de la f�sica cada frame
void PhysicsManager::Tick()
{
	//Avanzar el mundo
	world->Step(TIMESTEP, VELOCITYITERATIONS, POSITIONITERATIONS);
}

//M�todo llamado cuando dos cuerpos colisionan
void PhysicsManager::BeginContact(b2Contact* contact)
{
	b2Fixture *f1 = contact->GetFixtureA();
	b2Fixture *f2 = contact->GetFixtureB();

	GameObject * g1 = (GameObject*)f1->GetBody()->GetUserData();
	GameObject * g2 = (GameObject*)f2->GetBody()->GetUserData();

	//Se detecta cuando los dos objetos empiezan a colisionar
	g1->OnCollisionEnter((ColliderComponent*)g2->GetComponent(COLLIDER));
	g2->OnCollisionEnter((ColliderComponent*)g1->GetComponent(COLLIDER));
}

//M�todo llamado cuando dos cuerpos dejan de colisionar
void PhysicsManager::EndContact(b2Contact* contact)
{
	b2Fixture *f1 = contact->GetFixtureA();
	b2Fixture *f2 = contact->GetFixtureB();

	GameObject * g1 = (GameObject*)f1->GetBody()->GetUserData();
	GameObject * g2 = (GameObject*)f2->GetBody()->GetUserData();

	//Se detecta cuando los dos objetos ya no est�n colisionando
	if (g1 != nullptr)
		g1->OnCollisionExit((ColliderComponent*)g2->GetComponent(COLLIDER));
	if (g2 != nullptr)
		g2->OnCollisionExit((ColliderComponent*)g1->GetComponent(COLLIDER));
}

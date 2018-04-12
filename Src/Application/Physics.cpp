#include "Physics.h"


Physics::Physics()
{
	numObj = 0;
	initObjects();
}


Physics::~Physics()
{
}

//Constructor del Physics Manager
//Crea un mundo dinámico preparado para aceptar nuestros objetos en él
void Physics::initObjects() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
	dynamicsWorld->applyGravity();

}

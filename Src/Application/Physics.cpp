#include "Physics.h"


Physics::Physics()
{
	initObjects();
}


Physics::~Physics()
{
}

//Constructor del Physics Manager
//Crea un mundo din�mico preparado para aceptar nuestros objetos en �l
void Physics::initObjects() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

}

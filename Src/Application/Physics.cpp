#include "Physics.h"


Physics::Physics()
{
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

}

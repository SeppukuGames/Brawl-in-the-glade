#include "Physics.h"


Physics::Physics()
{
	initObjects();
}


Physics::~Physics()
{
	// Clean up behind ourselves like good little programmers
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

//Constructor del Physics Manager
//Crea un mundo din�mico preparado para aceptar nuestros objetos en �l
void Physics::initObjects() {

	//Escoger el algoritmo de detecci�n de colisiones. Hay muchos algoritmos. Detecta pares de colisiones
	broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	collisionConfiguration = new btDefaultCollisionConfiguration();	//Permite tunear los algoritmos usados para la detecci�n de colisiones
	dispatcher = new btCollisionDispatcher(collisionConfiguration);	//registra un callback que filtra las superposiciones haciendo que el sistema no procese las colisiones que no nos interesan

	// The actual physics solver
	solver = new btSequentialImpulseConstraintSolver();

	//Instanciamos el mundo din�mico
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

}

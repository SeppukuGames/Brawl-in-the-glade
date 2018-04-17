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

	//Escoger el algoritmo de detecci�n de colisiones. Hay muchos algoritmos. Detecta pares de colisiones
	broadphase = new btDbvtBroadphase();

	//Permite tunear los algoritmos usados para la detecci�n de colisiones
	collisionConfiguration = new btDefaultCollisionConfiguration();
	//registra un callback que filtra las superposiciones haciendo que el sistema no procese las colisiones que no nos interesan
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver();

	//Instanciamos el mundo din�mico
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

}

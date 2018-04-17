#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "btBulletCollisionCommon.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

#include <vector>
#include <map>

//Physics Manager
class Physics{
	//Escoger el algoritmo de detección de colisiones. Hay muchos algoritmos. Detecta pares de colisiones
	btBroadphaseInterface* broadphase;

	//Permite tunear los algoritmos usados para la detección de colisiones
	btDefaultCollisionConfiguration* collisionConfiguration;

	//registra un callback que filtra las superposiciones haciendo que el sistema no procese las colisiones que no nos interesan
	btCollisionDispatcher* dispatcher;

	/*Si introducimos diferentes tipos de colisión de objetos
	(por ejemplo meshes usando btGImpachMeshShape)
	necesitamos registrar un algoritmo de colisiones 
	para obtener las colisiones reconocidas*/
	//btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

	/*Causa que los objetos interactuen adecuadamente, teniendo en cuenta
	la gravedad, lógica del juego, fuerzas, colisiones, etc*/
	//Hay otras versiones para mejorar el rendimiento
	btSequentialImpulseConstraintSolver* solver;

	//Mundo
	btDiscreteDynamicsWorld* dynamicsWorld;

	std::vector<btCollisionShape *> collisionShapes;
	std::map<std::string, btRigidBody *> physicsAccessors;

	void initObjects();
public:
	Physics::Physics();
	Physics::~Physics();

	inline btDiscreteDynamicsWorld* getDynamicsWorld(){ return dynamicsWorld; }
	inline std::vector<btCollisionShape *> getCollisionShapes(){ return collisionShapes; }
	inline int getCollisionObjectCount(){ return dynamicsWorld->getNumCollisionObjects(); }

	inline void trackRigidBodyWithName(btRigidBody * body, std::string name){ physicsAccessors.insert({ name, body }); };

};
#endif /* PHYSICS_H_ */
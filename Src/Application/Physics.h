#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "btBulletCollisionCommon.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include <vector>
#include <map>

//Physics Manager
class Physics{
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
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
#ifndef __PhysicsManager_h_
#define __PhysicsManager_h_

#include <Box2D.h>

#define TIMESTEP 1.0f/60.0f
#define VELOCITYITERATIONS 6
#define POSITIONITERATIONS 2
#define GRAVITY -10

class PhysicsManager
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static PhysicsManager *instance;

	/* Private constructor to prevent instancing. */
	PhysicsManager();

	~PhysicsManager();

public:
	/* Static access method. */
	static PhysicsManager * GetInstance();

	static void ResetInstance();
#pragma endregion Singleton

private:
	b2World *world;

public:
	void InitPhysics();
	void Tick();

	inline b2World * GetWorld(){ return world; };

};
#endif // #ifndef __PhysicsManager_h_

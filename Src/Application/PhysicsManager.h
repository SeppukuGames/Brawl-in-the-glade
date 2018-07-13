#ifndef __PhysicsManager_h_
#define __PhysicsManager_h_

#include <Box2D.h>

#define TIMESTEP 1.0f/60.0f
#define VELOCITYITERATIONS 6
#define POSITIONITERATIONS 2
#define GRAVITY -10

class PhysicsManager: public b2ContactListener
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
	void InitPhysics();			//Método encargado de inicializar la física
	void Tick();				//Método que actualiza el estado de la física cada frame

	virtual void BeginContact(b2Contact* contact);	//Método llamado cuando dos cuerpos colisionan
	virtual void EndContact(b2Contact* contact);	//Método llamado cuando dos cuerpos dejan de colisionar

	inline b2World * GetWorld(){ return world; };	//Método que devuelve la referencia del mundo

};
#endif // #ifndef __PhysicsManager_h_


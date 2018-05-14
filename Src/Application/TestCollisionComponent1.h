#ifndef TESTCOLLISIONCOMPONENT1_H_
#define TESTCOLLISIONCOMPONENT1_H_

#include "Component.h"

class TestCollisionComponent1 : public Component{
public:
	TestCollisionComponent1();

	virtual ~TestCollisionComponent1();

	virtual void start();

	virtual void tick();

	virtual void onCollision(GameObject *collision);

};

#endif /* TESTCOLLISIONCOMPONENT1_H_ */
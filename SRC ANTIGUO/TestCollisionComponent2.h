#ifndef TESTCOLLISIONCOMPONENT2_H_
#define TESTCOLLISIONCOMPONENT2_H_

#include "Component.h"

class TestCollisionComponent2 : public Component{
public:
	TestCollisionComponent2();

	virtual ~TestCollisionComponent2();

	virtual void start();

	virtual void tick();

	virtual void mePegan();

};

#endif /* TESTCOLLISIONCOMPONENT2_H_ */
#include "TestCollisionComponent1.h"
#include <iostream>
#include "GameObject.h"
#include "TestCollisionComponent2.h"

TestCollisionComponent1::TestCollisionComponent1()
{
}


TestCollisionComponent1::~TestCollisionComponent1()
{
}

void TestCollisionComponent1::start(){

}

void TestCollisionComponent1::tick(){

}

void  TestCollisionComponent1::onCollision(GameObject *collision)
{
	if (collision != nullptr)
	{

		std::cout << "Colision con " + collision->getNode()->getName() + '\n';

		//Detectamos de que tipo es la colisión de esta manera
		TestCollisionComponent2* testComp = dynamic_cast<TestCollisionComponent2*> (collision->getComponent(ComponentName::TESTCOLLISIONCOMPONENT2));
		if (testComp != nullptr)
		{
			testComp->mePegan();
		}

	}
	else{}
		//std::cout << "Colision con objeto estático" + '\n';
};
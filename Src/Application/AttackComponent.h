#ifndef ATTACKCOMPONENT_H_
#define ATTACKCOMPONENT_H_

#include "KeyInputComponent.h"

class AttackComponent : public KeyInputComponent{
public:

	AttackComponent() : KeyInputComponent()
	{

	};
	virtual ~AttackComponent() {};

	virtual void start();
	virtual void tick(double elapsed);





private:



};

#endif /* ATTACKCOMPONENT_H_ */

#ifndef __GameManager_h_
#define __GameManager_h_

#include "Component.h"

class GameManager : public Component{

#pragma region Attributes  
private:


#pragma endregion Attributes

#pragma region Methods  

public:
	GameManager(){};
	virtual ~GameManager(){};

	virtual void Update(double elapsed);


#pragma endregion Methods

};

#endif /* __GameManager_h_ */
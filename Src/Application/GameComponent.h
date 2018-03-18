#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "Component.h"

//GameObject compuesto por componentes
class GameComponent : public GameObject {

	std::vector<Component*> components;

public:
	GameComponent(Ogre::SceneNode* scnNode) ;
	virtual ~GameComponent();

	virtual void addComponent(Component* comp);

	// from GameObject
	virtual void tick();
};

#endif /* GAMECOMPONENT_H_ */

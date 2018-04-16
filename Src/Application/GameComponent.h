#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "Component.h"

//HAY QUE BORRAR ESTO ENTERO: EL H Y EL CPP

//GameObject compuesto por componentes
class GameComponent : public GameObject {

	std::vector<Component*> components;

public:
	GameComponent(Ogre::SceneManager * mSceneMgr);
	virtual ~GameComponent();

	virtual void addComponent(Component* comp);

	// from GameObject
	virtual void tick(double elapsed);
};

#endif /* GAMECOMPONENT_H_ */

#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "Component.h"
#include <OIS.h>
#include "NewMOC.h"
#include <OgreEntity.h>

/*ESTA CLASE DEBERIA FUNCIONAR POR MENSAJES, DEBERIA LLAMAR AL TRANSFORM COMPONENT*/
class MoveComponent : public Component, public OIS::KeyListener
{
public:
	MoveComponent(Collision::CollisionTools* col) : Component()
	{
		collision = col;
	};
	virtual ~MoveComponent(){
		collision->remove_entity(_entity);

	};

	virtual void start(){
		_nodo = _gameObject->getNode();
		_entity = _gameObject->getNode()->getCreator()->createEntity("ogrehead.mesh");
		_nodo->showBoundingBox(true);
		_gameObject->getNode()->attachObject(_entity);

		ray = new Ogre::Ray(_nodo->getPosition(), Ogre::Vector3(1,0,0));

		collision->register_entity(_entity, Collision::COLLISION_BOX);
	};
	virtual void tick(){

	};

	virtual bool keyPressed(const OIS::KeyEvent &arg){

		if (arg.key == OIS::KC_W)
		{
			_nodo->setPosition(Ogre::Vector3(_nodo->getPosition().x + 5, _nodo->getPosition().y, _nodo->getPosition().z));
		}

		if (arg.key == OIS::KC_A)
		{
			_nodo->setPosition(Ogre::Vector3(_nodo->getPosition().x - 5, _nodo->getPosition().y, _nodo->getPosition().z));
		}

		if (arg.key == OIS::KC_S)
		{
			_nodo->setPosition(Ogre::Vector3(_nodo->getPosition().x, _nodo->getPosition().y + 5, _nodo->getPosition().z));
		}

		if (arg.key == OIS::KC_D)
		{
			_nodo->setPosition(Ogre::Vector3(_nodo->getPosition().x, _nodo->getPosition().y - 5, _nodo->getPosition().z));
		}
		Collision::SCheckCollisionAnswer ret = collision->check_ray_collision(*ray);

		// check if we found collision:
		if (ret.collided)
		{
			int a = 0;
			// handle collision here..
		}

		return true;
	}
	virtual bool keyReleased(const OIS::KeyEvent &arg){

		return true;

	}

private:
	Ogre::SceneNode* _nodo;
	Ogre::Entity * _entity;

	Ogre::Ray* ray;

	Collision::CollisionTools* collision;//Puntero al manager
};

#endif /* MoveComponentCOMPONENT_H_ */
#include "GameObject.h"
#include "SceneManager.h"

#include "EntityComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "AudioComponent.h"
#include "Error.h"

GameObject::GameObject(std::string name) :components(0){
	control = new UserControl(this);
	node = SceneManager::GetInstance()->GetCurrentScene()->GetSceneMgr()->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0, 0, 0));
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}

	delete control;
}

void GameObject::Tick(double elapsed) {
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Update(elapsed);
}

void GameObject::AddComponent(Component* comp) {
	components.push_back(comp);
	comp->SetGameObject(this);
	comp->Start();
}

Component* GameObject::GetComponent(ComponentName component) {

	switch (component)
	{
	case ComponentName::ENTITY:
		for (size_t i = 0; i < components.size(); i++)
		{
			EntityComponent* comp = dynamic_cast<EntityComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::COLLIDER:
		for (size_t i = 0; i < components.size(); i++)
		{
			ColliderComponent* comp = dynamic_cast<ColliderComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::BOXCOLLIDER:
		for (size_t i = 0; i < components.size(); i++)
		{
			BoxColliderComponent* comp = dynamic_cast<BoxColliderComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::CIRCLECOLLIDER:
		for (size_t i = 0; i < components.size(); i++)
		{
			CircleColliderComponent* comp = dynamic_cast<CircleColliderComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::RIGIDBODY:
		for (size_t i = 0; i < components.size(); i++)
		{
			RigidbodyComponent* comp = dynamic_cast<RigidbodyComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;

	case ComponentName::LIGHT:
		for (size_t i = 0; i < components.size(); i++)
		{
			LightComponent * comp = dynamic_cast<LightComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::CAMERA:
		for (size_t i = 0; i < components.size(); i++)
		{
			CameraComponent * comp = dynamic_cast<CameraComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;
	case ComponentName::AUDIO:
		for (size_t i = 0; i < components.size(); i++)
		{
			AudioComponent * comp = dynamic_cast<AudioComponent*>(components[i]);

			if (comp != NULL)
				return components[i];
		}

		break;

	default:
		throw(Error("Construye el GetComponent del nuevo Componente"));
	}

	return NULL;
}

//Es llamado cuando dos gameObject colisionan. Informa a todos sus componentes
void GameObject::OnCollisionEnter(ColliderComponent* collider){
	for (size_t i = 0; i < components.size(); i++)
		components[i]->OnCollisionEnter(collider);
}

//Es llamado cuando dos gameObject dejan de colisionar. Informa a todos sus componentes
void GameObject::OnCollisionExit(ColliderComponent* collider){
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] != nullptr)
			components[i]->OnCollisionExit(collider);
	}
}


void GameObject::SetObjMan(Ogre::MovableObject* mObj) {
	node->attachObject(mObj);
	node->getAttachedObject(node->numAttachedObjects() - 1)->getUserObjectBindings().setUserAny(Ogre::Any(control));
}

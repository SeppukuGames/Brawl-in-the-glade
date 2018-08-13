#include "GameObject.h"
#include "Component.h"

#include "StatsComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <random>

#include "PrefabManager.h"

using namespace rapidxml;

class lectorXML{
public:

	Ogre::Vector2 generarVector2(xml_node<> * component_node)
	{
		//atoi, para convertirlo a enteros
		Ogre::Vector2 vectorAux(atoi(component_node->first_attribute("x")->value()),
			atoi(component_node->first_attribute("y")->value()));

		return vectorAux;
	}

	Ogre::Vector3 generarVector3(xml_node<> * component_node)
	{
		
		if (component_node->first_attribute("random")) {
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 eng(rd()); // seed the generator
			std::uniform_int_distribution<> distrX(100, 200); // define the range
			std::uniform_int_distribution<> distrZ(150, 250); // define the range

			int x = distrX(eng);
			int z = distrZ(eng);

			Ogre::Vector3 vectorAux(x, 0, z);
			return vectorAux;
		}

		else {
			//atoi, para convertirlo a enteros
			Ogre::Vector3 vectorAux(atoi(component_node->first_attribute("x")->value()),
				atoi(component_node->first_attribute("y")->value()),
				atoi(component_node->first_attribute("z")->value()));

			return vectorAux;
		}
	}

	PREFABTYPE identificarPrefab(const std::string texto)
	{
		if (texto == "Camara")
			return PREFABTYPE::MAINCAMERA;
		if (texto == "Player")
			return PREFABTYPE::PLAYERPREFAB;
		if (texto == "GameManager")
			return PREFABTYPE::GAMEMANAGERPREFAB;
		if (texto == "Light")
			return PREFABTYPE::LIGHTPREFAB;
		if (texto == "Torre")
			return PREFABTYPE::TOWERPREFAB;
		if (texto == "Enemigo")
			return PREFABTYPE::ENEMYPREFAB;

		return PREFABTYPE::NULO; //En caso de meter un elemento inexistente o mal escrito
	}

	void identificarComponente(GameObject* gameObject, xml_node<> * component_node)
	{
		std::string nombreComponente = component_node->first_attribute("name")->value();
		if (nombreComponente == "Stats")
		{
			StatsComponent* componente;
			//Si no tiene StatsComponent, lo crea
			if (!gameObject->GetComponent(ComponentName::STATS)){
				componente = new StatsComponent();
				gameObject->AddComponent(componente);
			}
			else
				componente = (StatsComponent*)gameObject->GetComponent(ComponentName::STATS);

			if (component_node->first_attribute("vida")) //Si existe
				componente->SetLife(atoi(component_node->first_attribute("vida")->value()));

			if (component_node->first_attribute("maxVida")) //Si existe
				componente->SetLife(atoi(component_node->first_attribute("maxVida")->value()));

		}

		if (nombreComponente == "Posicion")
		{
			Ogre::Vector3 posicion = generarVector3(component_node);
			gameObject->GetNode()->setPosition(posicion);
		}

		if (nombreComponente == "BoxCollider")
		{
			BoxColliderComponent* componente;
			Ogre::Vector2 size = generarVector2(component_node);
			componente = new BoxColliderComponent(size.x, size.y);
			gameObject->AddComponent(componente);
		}

		if (nombreComponente == "Rigidbody")
			gameObject->AddComponent(new RigidbodyComponent(false, 1.0f));

	}

	bool DevuelveActivo(const std::string estado)
	{
		return estado == "si";
	}

	void AjustesPosteriores(GameObject* gameObject, PREFABTYPE tipoPrefab)
	{
		if (tipoPrefab == PREFABTYPE::ENEMYPREFAB)
			gameObject->AddComponent(new EnemyComponent(enemyType::ENEMY1));

		if (tipoPrefab == PREFABTYPE::PLAYERPREFAB)
			gameObject->AddComponent(new PlayerComponent());
	}

	void Leer(const std::string archivo)
	{
		xml_document<> doc;
		xml_node<> * root_node;
		GameObject* gameObject = nullptr;

		// Read the xml file into a vector
		std::ifstream theFile(archivo);

		std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);

		// Find our root node
		root_node = doc.first_node("Juego");

		// Iterate over the entities
		for (xml_node<> * entity_node = root_node->first_node("Entidad"); entity_node; entity_node = entity_node->next_sibling())
		{
			PREFABTYPE tipoPrefab = identificarPrefab(entity_node->first_attribute("name")->value());
			bool activo = DevuelveActivo(entity_node->first_attribute("activo")->value());
			if (tipoPrefab != PREFABTYPE::NULO && activo)
			{
				GameObject* gameObject = PrefabManager::GetInstance()->CreateObject(tipoPrefab);

				// Interate over the components								
				for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
				{
					identificarComponente(gameObject, component_node);
				}

				//Funcion especial para player y enemies
				AjustesPosteriores(gameObject, tipoPrefab);

			}
		}


		for (xml_node<> * entity_node = root_node->first_node("Entidades"); entity_node; entity_node = entity_node->next_sibling())
		{
			PREFABTYPE tipoPrefab = identificarPrefab(entity_node->first_attribute("name")->value());
			bool activo = DevuelveActivo(entity_node->first_attribute("activo")->value());
			int numeroPrefabs = atoi(entity_node->first_attribute("numero")->value());

			if (tipoPrefab != PREFABTYPE::NULO && activo)
			{
				for (int i = 0; i < numeroPrefabs; i++)
				{

					GameObject* gameObject = PrefabManager::GetInstance()->CreateObject(tipoPrefab);

					// Interate over the components								
					for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
					{
						identificarComponente(gameObject, component_node);
					}

					//Funcion especial para player y enemies
					AjustesPosteriores(gameObject, tipoPrefab);
				}
			}
		}
	}

};
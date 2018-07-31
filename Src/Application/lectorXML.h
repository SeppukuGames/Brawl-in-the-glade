#include "GameObject.h"
#include "Component.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>

#include "PrefabManager.h"

using namespace rapidxml;

class lectorXML{
public:
	PREFABTYPE identificarPrefab(const std::string texto)
	{
		if (texto == "Camara")
			return PREFABTYPE::MAINCAMERA;
		if (texto == "Ninja")
			return PREFABTYPE::NINJAPREFAB;
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
	
	Component* identificarComponente(xml_node<> * component)
	{
		//if (component->first_attribute("name")->value() == "posicion")
		//component_node->value(); //Acceder al valor del componente
	}

	std::vector<GameObject*> Leer(const std::string archivo)
	{
		std::vector<GameObject*> gameObjects_;
		xml_document<> doc;
		xml_node<> * root_node;

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
			if (tipoPrefab != PREFABTYPE::NULO){
				GameObject* aux = PrefabManager::GetInstance()->CreateObject(tipoPrefab);

				// Interate over the components		
				/*En proceso
				for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
				{
				Component* componente = identificarComponente(component_node);
				aux->AddComponent(componente);
				}	*/

				gameObjects_.push_back(aux);
			}
		}
		return gameObjects_;
	}

};
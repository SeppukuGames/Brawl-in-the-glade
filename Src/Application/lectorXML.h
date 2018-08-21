#include "GameObject.h"
#include "Component.h"

#include "StatsComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "Boton.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>
#include <random>

#include "PrefabManager.h"

#include "MenuComponent.h"

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

	std::uniform_int_distribution<> identificadorSpawns(std::string spawn, std::string coordenada) {
		if (spawn == "spawn1") {
			if (coordenada == "x") {
				std::uniform_int_distribution<> distrX(100, 200);
				return distrX;
			}
			if (coordenada == "z") {
				std::uniform_int_distribution<> distrZ(100, 200);
				return distrZ;
			}
		}

		if (spawn == "spawnArbol") {
			if (coordenada == "x") {
				std::uniform_int_distribution<> distrX(100, 200);
				return distrX;
			}
			if (coordenada == "z") {
				std::uniform_int_distribution<> distrZ(100, 200);
				return distrZ;
			}
		}
	}

	Ogre::Vector3 generarVector3(xml_node<> * component_node)
	{
		if (component_node->first_attribute("random")) {
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 eng(rd()); // seed the generator

			std::string spawn = component_node->first_attribute("random")->value();
			std::uniform_int_distribution<> distrX = identificadorSpawns(spawn, "x");// define the range
			std::uniform_int_distribution<> distrZ = identificadorSpawns(spawn, "z"); // define the range

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
		if (texto == "Enemigo1")
			return PREFABTYPE::ENEMY1PREFAB;
		if (texto == "Enemigo2")
			return PREFABTYPE::ENEMY2PREFAB;
		if (texto == "Arbol")
			return PREFABTYPE::ARBOLPREFAB;
		if (texto == "Arbol_new")
			return PREFABTYPE::ARBOL_NEWPREFAB;
		if (texto == "Arbol2")
			return PREFABTYPE::ARBOL2PREFAB;
		if (texto == "Arbol3")
			return PREFABTYPE::ARBOL3PREFAB;
		if (texto == "Arbol4")
			return PREFABTYPE::ARBOL4PREFAB;
		if (texto == "Arbol5")
			return PREFABTYPE::ARBOL5PREFAB;
		if (texto == "Menu")
			return PREFABTYPE::MENU;
		if (texto == "Ogro")
			return PREFABTYPE::MUROPREFAB;


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
				componente->SetMaxLife(atoi(component_node->first_attribute("maxVida")->value()));
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

		if (nombreComponente == "Menu"){
			gameObject->AddComponent(new MenuComponent(component_node->first_attribute("imagen")->value()));
		}

		if (nombreComponente == "Boton")
		{
			Component* aux = gameObject->GetComponent(ComponentName::MENUCOMPONENT);
			int n = static_cast<MenuComponent*>(aux)->getNumButtons();
			Boton* boton = new Boton(component_node->first_attribute("texto")->value(), n);
			boton->setAction(component_node->first_attribute("tipo")->value());
			static_cast<MenuComponent*>(aux)->AddButton(boton);	
		}

	}

	bool DevuelveActivo(const std::string estado)
	{
		return estado == "si";
	}

	//TODO: ver si debería ir aqui el componente STATS independientemente de qué tipo de objeto sea.
	void AjustesPosteriores(GameObject* gameObject, PREFABTYPE tipoPrefab)
	{
		if (tipoPrefab == PREFABTYPE::ENEMY1PREFAB){
			//Importante: Tiene que tener un enemyComponent previo
			gameObject->AddComponent(new EnemyComponent(enemyType::ENEMY1));
			gameObject->AddComponent(new StatsComponent());
		}

		if (tipoPrefab == PREFABTYPE::ENEMY2PREFAB){
			//Importante: Tiene que tener un enemyComponent previo
			gameObject->AddComponent(new EnemyComponent(enemyType::ENEMY2));
			gameObject->AddComponent(new StatsComponent());
		}

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
			int numeroPrefabs = 1;
			if (entity_node->first_attribute("numero"))
				numeroPrefabs = atoi(entity_node->first_attribute("numero")->value());

			if (tipoPrefab != PREFABTYPE::NULO && activo)
			{
				if (numeroPrefabs == 1) {
					GameObject* gameObject = PrefabManager::GetInstance()->CreateObject(tipoPrefab);

					// Interate over the components								
					for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
					{
						identificarComponente(gameObject, component_node);
					}

					//Funcion especial para player y enemies
					AjustesPosteriores(gameObject, tipoPrefab);
					PrefabManager::GetInstance()->insertObjectIntoCurrentScene(gameObject);
				}

				else {
					std::list<xml_node<> *>listaComponentes;
					for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
					{
						listaComponentes.push_back(component_node);
					}

					for (int i = 0; i < numeroPrefabs; i++) {
						GameObject* gameObject = PrefabManager::GetInstance()->CreateObject(tipoPrefab);

						for (std::list<xml_node<> *>::const_iterator iter = listaComponentes.begin(); iter != listaComponentes.end(); ++iter)
						{
							identificarComponente(gameObject, *iter);
						}

						AjustesPosteriores(gameObject, tipoPrefab);
						PrefabManager::GetInstance()->insertObjectIntoCurrentScene(gameObject);
					}
				}
				
			}
		}
	}

};
//#include "MainGame.h"
#include "Home.h"
//#include "TutorialBuffered.h"
//#include "tutorial2.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <iostream>

using namespace rapidxml;

// https://stackoverflow.com/questions/8720215/how-can-i-write-rapidxml-content-to-file-in-mfc
int crearXML()
{
	xml_document<> doc;
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
	doc.append_node(decl);

	xml_node<> *files = doc.allocate_node(node_element, "Files");
	doc.append_node(files);
	xml_attribute<> *attr = doc.allocate_attribute("dummy", "google.com");
	files->append_attribute(attr);

	for (int i = 0; i < 4; ++i)
	{
		xml_node<> *file = doc.allocate_node(node_element, "File");
		files->append_node(file);

		xml_node<> *path = doc.allocate_node(node_element, "Path", "File_path");
		file->append_node(path);
		xml_node<> *name = doc.allocate_node(node_element, "Name""File_name");
		file->append_node(name);
	}

	std::ofstream myfile;
	myfile.open("xmlGenerado.xml");
	myfile << doc;
	std::cout << "-----------IMPRIMIENDO XML-----------" << std::endl;
	print(std::cout, doc, 0);
	std::cout << "Archivo xml creado" << std::endl;
	return 0;
}

// http://www.setnode.com/blog/quick-notes-on-how-to-use-rapidxml/
void traverse_xml(const std::string& input_xml)
{
	// (input_xml contains the above XML)

	// make a safe-to-modify copy of input_xml
	// (you should never modify the contents of an std::string directly)
	std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');

	// only use xml_copy from here on!
	xml_document<> doc;
	// we are choosing to parse the XML declaration
	// parse_no_data_nodes prevents RapidXML from using the somewhat surprising
	// behavior of having both values and data nodes, and having data nodes take
	// precedence over values when printing
	// >>> note that this will skip parsing of CDATA nodes <<<
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	// alternatively, use one of the two commented lines below to parse CDATA nodes, 
	// but please note the above caveat about surprising interactions between 
	// values and data nodes (also read http://www.setnode.com/blog/a-rapidxml-gotcha/)
	// if you use one of these two declarations try to use data nodes exclusively and
	// avoid using value()
	//doc.parse<parse_declaration_node>(&xml_copy[0]); // just get the XML declaration
	//doc.parse<parse_full>(&xml_copy[0]); // parses everything (slowest)

	// since we have parsed the XML declaration, it is the first node
	// (otherwise the first node would be our root node)
	std::string encoding = doc.first_node()->first_attribute("encoding")->value();
	// encoding == "utf-8"

	// we didn't keep track of our previous traversal, so let's start again
	// we can match nodes by name, skipping the xml declaration entirely
	xml_node<>* cur_node = doc.first_node("rootnode");
	std::string rootnode_type = cur_node->first_attribute("type")->value();
	// rootnode_type == "example"

	// go straight to the first evendeepernode
	cur_node = cur_node->first_node("childnode")->first_node("evendeepernode");
	std::string attr2 = cur_node->first_attribute("attr2")->value();
	// attr2 == "dog"

	// and then to the second evendeepernode
	cur_node = cur_node->next_sibling("evendeepernode");
	attr2 = cur_node->first_attribute("attr2")->value();
	// now attr2 == "wolf"
}

// https://gist.github.com/JSchaenzle/2726944
void beerMain()
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile("pruebaTres.xml");

	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);

	// Find our root node
	root_node = doc.first_node("MyBeerJournal");

	// Iterate over the brewerys
	for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
	{
		printf("I have visited %s in %s. ",
			brewery_node->first_attribute("name")->value(),
			brewery_node->first_attribute("location")->value());
		// Interate over the beers
		for (xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
		{
			printf("On %s, I tried their %s which is a %s. ",
				beer_node->first_attribute("dateSampled")->value(),
				beer_node->first_attribute("name")->value(),
				beer_node->first_attribute("description")->value());
			printf("I gave it the following review: %s", beer_node->value());
		}
		std::cout << std::endl;
	}
}

void miIntento()
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile("intento.xml");

	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);

	// Find our root node
	root_node = doc.first_node("Juego");

	// Iterate over the entities
	for (xml_node<> * entity_node = root_node->first_node("Entidad"); entity_node; entity_node = entity_node->next_sibling())
	{
		printf("Mi entidad %s ",
			entity_node->first_attribute("name")->value());

		std::cout << "tiene los siguientes componentes: " << std::endl;
		// Interate over the components

		for (xml_node<> * component_node = entity_node->first_node("Componente"); component_node; component_node = component_node->next_sibling())
		{
			printf("Nombre: %s, valor: %s ",
				component_node->first_attribute("name")->value(),
				component_node->value());
		}
		std::cout << std::endl;
	}
}


#ifdef _DEBUG || !_WIN32
int main()
{
	printf("Hola, Mundo!\n");
#else
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){

#endif
	//Inicializa Ogre y el juego

	//crear_xml(); //crea un xml, guarda el fichero en ogreD e imprime
	//traverse_xml("<childnode entry=\"1\">"); //Aun no lo he hecho funcionar, deberia encontrar el atributo que le pases como parametro
	//pruebaDos(); //Intento fallido de iterar entre atributos, crea un nuevo atributo en el documento correctamente
	//beerMain(); //Permite leer un xml correctamente y lo imprime (pruebaTres.xml) //Lo mas parecido a miIntento, mas desarrollado aun
	miIntento();

	std::cout << "introduzca S para salir" << std::endl;
	char num = 'w';
	while (num != 's')
		std::cin >> num;


	//Home::getInstance()->go();	
	return 0;
}

/*TODO: Para que no salga la consola en modo release, tocar esto
#ifdef _DEBUG || !_WIN32

int main(){


#else //_RELEASE

#include <Windows.h> //Hay que incluir la API de windows

int CALLBACK WinMain(
_In_ HINSTANCE hInstance,
_In_ HINSTANCE hPrevInstance,
_In_ LPSTR lpCmdLine,
_In_ int nCmdShow) {

#endif

ProyectoBasico * pb = new ProyectoBasico();
pb->go();
return 0;
}*/
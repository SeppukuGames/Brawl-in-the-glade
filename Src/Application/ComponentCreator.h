#ifndef _H_ComponentCreator_H_
#define	_H_ComponentCreator_H_

#include "rapidxml.hpp"

class ComponentCreator {
public:
	ComponentCreator();
	virtual ~ComponentCreator();

protected:
	virtual void Parser(rapidxml::xml_node<>* node);
};

// Aqui debajo iran todos los componentes que necesiten datos de un xml
class RandomComponent : public ComponentCreator {
public:
	RandomComponent();
	// RandomComponent(rapidxml::xml_node<>* node) : parametros que utilizara el componente{
	// Parser(node);
	// }
	virtual ~RandomComponent();

private:
	void Parser(rapidxml::xml_node<>* node) {}
};
#endif
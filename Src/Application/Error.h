#ifndef Error_H
#define Error_H

#include <string>

using namespace std;

//Para las excepciones que lanzará el juego al iniciarse
class Error
{
public:
	Error(string const & mensaje): mensajeError(mensaje){};
	virtual ~Error(){};

	const string& mensaje() const{ return mensajeError; }

protected:
	string mensajeError;
};


#endif
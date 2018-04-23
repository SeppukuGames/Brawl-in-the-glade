#ifndef Mensaje_H_
#define Mensaje_H_

#include <vector>
#include "AnimationComponent.h" //Para el enum


//Clase abstracta para las demás
class Mensaje
{

	class GameObject; //Le decimos que existe
public:
	enum TipoMensaje { MensajeBala, MensajeMovimiento };
};
#endif


class MensajeBala : public Mensaje {

public:
	MensajeBala(TipoMensaje tipo,
		double posX, double posY, double posZ,
		double dirX, double dirY, double dirZ,
		int dañoProyectil
		) {
		_tipo = tipo;

		_posX = posX;
		_posY = posY;
		_posY = posY;

		_dirX = dirX;
		_dirY = dirY;
		_dirZ = dirZ;

		_dañoProyectil = dañoProyectil;
	}

	TipoMensaje _tipo;

	double _posX, _posY, _posZ;
	double _dirX, _dirY, _dirZ;
	int _dañoProyectil;

};

class MensajeMovimiento : public Mensaje {

public:
	MensajeMovimiento(TipoMensaje tipo) {


	}
};

//Mensaje del componente animación
class MensajeAnimacion : public Mensaje {

public:
	MensajeAnimacion(std::string animacion, AnimationComponent::BlendingTransition blending, double duracion, bool loop) {
		_animacion = animacion;
		_blending = blending;
		_duracion = duracion;
		_loop = loop;

	}

	std::string _animacion;
	AnimationComponent::BlendingTransition _blending;
	double _duracion;
	bool _loop;
};
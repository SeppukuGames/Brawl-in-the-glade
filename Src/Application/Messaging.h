#pragma once

#include <vector> // Para almacenar la lista de senders y listeners

// Esto va a ser un tipo especifico de mensajes y queremos tener diferentes tipos
struct VectorMessage {
	// Es un area bidimensional que determina a quien va el mensaje
	// Es un punto y una direccion
	// Sirve para proyectar nuestra clase y "disparar un proyectil",
	// a partir de un punto (x1, y1) en la dirección (x2, y2)
	float x1;
	float x2;
	float y1;
	float y2;
};

// Las dos siguientes clases tienen el nombre de VectorX para que sirva en caso de que
// creemos distintos tipos de emisores y receptores

class VectorSender {

public:
	VectorSender();
	~VectorSender();

	void SendMessage(float x1, float y1, float x2, float y2); // Podemos pasar por parametro un VectorMessage message
															  // Si ponemos eso, hay que asegurarse de haber construido
															  // el mensaje para despues enviarlo.
															  // La clase Message construira el mensaje por sí misma.
	void recieveListener(VectorListener * listener);

private:
	std::vector<VectorListener*> mListeners; // Vector de miembros que son listeners
};

class VectorListener {

public:
	VectorListener();
	~VectorListener();

	void listenToSender(VectorSender * sender);
	std::vector<float> GetMessage(); // devuelve el primer mensaje (las dos coordenadas) de la pila
	void recieveMessage(VectorMessage newMessage);

private:
	std::vector<VectorMessage> mMessages;
};


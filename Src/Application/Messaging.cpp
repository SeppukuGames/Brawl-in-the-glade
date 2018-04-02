#include "Messaging.h"

// VectorSender
VectorSender::VectorSender() {

}

VectorSender::~VectorSender() {

}

void VectorSender::SendMessage(float x1, float y1, float x2, float y2) {

	VectorMessage newMessage;
	newMessage.x1 = x1;
	newMessage.y1 = y1;
	newMessage.x2 = x2;
	newMessage.y2 = y2;

	/*for (unsigned int i = 0; i < mListeners.size(); i++)
	{
		mListeners[i]->recieveMessage(newMessage);
	}*/

	for each (VectorListener* i in mListeners)
	{
		i->recieveMessage(newMessage);
	}
	
	
}

void VectorSender::recieveListener(VectorListener * listener) {
	mListeners.push_back(listener);
}
// VectorSender

// VectorListener
VectorListener::VectorListener(){
}

VectorListener::~VectorListener(){

}



void VectorListener::listenToSender(VectorSender * sender) {
	// Escuchamos al remitente
	sender->recieveListener(this); // un puntero a si mismo
}

std::vector<float> VectorListener::GetMessage() {
	
	std::vector<float> messageVector;
	for (size_t i = 0; i < mMessages.size(); i++)
	{
		messageVector.push_back(mMessages[i].x1);
		messageVector.push_back(mMessages[i].y1);
		messageVector.push_back(mMessages[i].x2);
		messageVector.push_back(mMessages[i].y2);
	}

	messageVector.clear();
	return messageVector;
}

void VectorListener::recieveMessage(VectorMessage newMessage) {
	mMessages.push_back(newMessage);
}
// VectorListener


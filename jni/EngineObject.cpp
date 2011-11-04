#include "EngineObject.h"

Node* EngineStack = new Node("init");

int JNIEngineFlag = 1;

//Engine Call Stack to JNI
//We use this to ask for models/textures/etc to load.
void EngineStackpush(const char* str){
	EngineStack->addNext(new Node(str));
}

Node* EngineStackpop()
{
	Node * return_v = EngineStack;
	EngineStack = EngineStack->next;
	return return_v;
}


Node::Node(const char * str)
{
	this->string = str;
}

void Node::addNext(Node * n){
	this->next = n;
}

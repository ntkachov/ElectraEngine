#ifndef Engine_Object_h
#define Engine_Object_h

class Node
{
public:
	Node* next;
	const char* string;
	Node(const char * str);
	void addNext(Node * n);
};


extern void EngineStackpush(const char* str);
extern Node* EngineStackpop();

#endif

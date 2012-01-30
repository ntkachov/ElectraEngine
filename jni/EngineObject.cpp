#include "EngineObject.h"
#include <queue>

using namespace std;
queue<const char*> engineQueue; //= new queue<const char *>();

int JNIEngineFlag = 1;



//Engine Call Stack to JNI
//We use this to ask for models/textures/etc to load.
void EngineStackpush(const char* str){
	engineQueue.push(str);
}

const char* EngineStackpop()
{
	const char * r = engineQueue.front();
	 engineQueue.pop();
	 return r;
}

int EngineFlag()
{
	if(engineQueue.empty())
		return 0;
	else
		return 1;
}

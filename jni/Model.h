#ifndef Model_h
#define Model_h

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Model{
private:

public:
	GLuint bufferID;
	int vertexNum;
	bool ready;
	Model(){}
	~Model(){}
	void onRemove(){ glDeleteBuffers(1, &bufferID); };
	void onLoad(int vertexSize, float * verts);
	void onDraw(GLuint gvPositionHandle);

};

#endif

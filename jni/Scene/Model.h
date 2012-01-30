#ifndef Model_h
#define Model_h

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Model{
private:

public:
	GLuint bufferID;
	GLuint textureID;
	int vertexNum;
	bool ready;
	glm::mat4 modelTrans;
	glm::mat3 Nmatrix;
	Model(){}
	~Model(){}
	void onRemove(){ glDeleteBuffers(1, &bufferID); };
	void onLoad(int vertexSize, float * Vertices, float * Normals, float * UV, float * position, float * rotation, GLubyte * texture, int size);
	void onDraw(GLuint gvPositionHandle, GLuint normals, GLuint model, GLuint normM, GLuint texture, GLuint textureU);

};

#endif

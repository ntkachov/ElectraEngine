#include "Model.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Helper.h"

glm::mat4 getTransform(glm::vec3 const & Translate, glm::vec3 const & Rotate){
	glm::mat4 Model = glm::scale(
				glm::mat4(1.0f),
				glm::vec3(0.5f));
	glm::mat4 ViewTranslate = glm::translate(
				glm::mat4(1.0f),
				Translate);
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
		glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 View = glm::rotate(ViewRotateY, Rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
		return View * Model;
}

void Model::onLoad(int vertexSize, float * Vertices, float * Normals, float * UV, float * position, float * rotation, GLubyte * texture, int size){
	//Set up VBOS
	this->vertexNum = vertexSize;
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ARRAY_BUFFER, this->vertexNum *  sizeof(float) * 8, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertexNum * sizeof(float), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, this->vertexNum * sizeof(float), this->vertexNum * sizeof(float), Normals);
	glBufferSubData(GL_ARRAY_BUFFER, this->vertexNum * sizeof(float) * 2, ((this->vertexNum * sizeof(float) *2)/3), UV );

	this->modelTrans = getTransform(glm::vec3(position[0],position[1],position[2]), glm::vec3(rotation[0],rotation[1],rotation[2]));
	this->Nmatrix = glm::transpose(glm::inverse(glm::mat3(this->modelTrans)));

	glGenTextures( 1, &this->textureID);
	glBindTexture( GL_TEXTURE_2D, this->textureID );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE,(const void *) texture);
	this->ready=true;
}

void Model::onDraw(GLuint gvPositionHandle, GLuint normals, GLuint modelM, GLuint normM, GLuint texture, GLuint textureU){
	glUniformMatrix4fv(modelM, 1, GL_FALSE, glm::value_ptr(this->modelTrans));
	glUniformMatrix3fv(normM, 1, GL_FALSE, glm::value_ptr(this->Nmatrix));
	//checkGlError("OnDraw");
	glEnableVertexAttribArray(gvPositionHandle);
	glEnableVertexAttribArray(normals);
	glEnableVertexAttribArray(texture);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, 0 , (const void *)(this->vertexNum *sizeof(float)));
	glVertexAttribPointer(texture, 2, GL_FLOAT, GL_FALSE, 0 , (const void *)(this->vertexNum *sizeof(float)*2));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glUniform1i(textureU, 0);
	checkGlError("glUniform1i");

	glDrawArrays(GL_TRIANGLES, 0, this->vertexNum/3);

	glDisableVertexAttribArray(gvPositionHandle);
	glDisableVertexAttribArray(normals);//
	glDisableVertexAttribArray(texture);
	// LOGI("Model Drawn");


}

#include "Model.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void checkGlError(const char* op) {
	for (GLint error = glGetError(); error; error
	= glGetError()) {
		LOGI("after %s() glError (0x%x)\n", op, error);
	}
}
static void printNum(int i){
	char strBuffer[4];
	sprintf(strBuffer, "%i", i);
	LOGI(strBuffer);
}
static void printFloat(float i){
	char strBuffer[4];
	sprintf(strBuffer, "%f", i);
	LOGI(strBuffer);
}

void Model::onLoad(int vertexSize, float * Vertices){
	//Set up VBOS
	this->vertexNum = vertexSize;
	//for(int i = 0; i < vertexSize; i++)
	//	printFloat(vertices[i]);
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ARRAY_BUFFER, (this->vertexNum) *  sizeof(float), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertexNum * sizeof(float), Vertices);
	this->ready=true;
//	LOGI("Model Loaded");
//	checkGlError("OnLoad");

}

void Model::onDraw(GLuint gvPositionHandle){
	glEnableVertexAttribArray(gvPositionHandle);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
			0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->vertexNum);
	//glDisableVertexAttribArray(gvPositionHandle);
	  glDisableVertexAttribArray(gvPositionHandle);
	 // LOGI("Model Drawn");
	  checkGlError("OnDraw");

}

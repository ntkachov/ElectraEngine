// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "EngineObject.h"
#include "Model.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


Model* modle = new Model();

static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

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

static const char gVertexShader[] = 
		"attribute vec4 vPosition;\n"
		//	"attribute vec4 SourceColor;\n"
		//	"varying vec4 DestinationColor;\n"
		"uniform mat4 modelViewMatrix;\n"
		"void main() {\n"
		//"DestinationColor = SourceColor;\n"
		"  gl_Position = modelViewMatrix * vPosition;\n"
		"}\n";

static const char gFragmentShader[] = 
		"precision mediump float;\n"
		//	"varying lowp vec4 DestinationColor;\n"
		"void main() {\n"
		"  gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);\n"
		"}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
	GLuint shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					LOGE("Could not compile shader %d:\n%s\n",
							shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
	if (!vertexShader) {
		return 0;
	}

	GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
	if (!pixelShader) {
		return 0;
	}

	GLuint program = glCreateProgram();
	if (program) {
		glAttachShader(program, vertexShader);
		checkGlError("glAttachShader");
		glAttachShader(program, pixelShader);
		checkGlError("glAttachShader");
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}

GLuint gProgram;
GLuint gvPositionHandle;
GLuint mvp_a_positionHandle;
GLuint _colorSlot;
float* Vertices;
//GLuint vertexBuffer;
/*
void setupVBO(){
//	vertexSize = sizeof(Vertices) / sizeof(float);
//	indiceSize = sizeof(Indices) / sizeof(int);
	glGenBuffers(1, &modle->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, modle->bufferID);
	glBufferData(GL_ARRAY_BUFFER, (modle->vertexNum) *  sizeof(float), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, modle->vertexNum * sizeof(float), Vertices);
	checkGlError("Vertex VBO");
	LOGI("Setup Called");
	/*glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize * sizeof(GLuint), Indices, GL_STATIC_DRAW);
	checkGlError("Index VBO");
}
void updateVBO(){
	glBufferData(GL_ARRAY_BUFFER, (modle->vertexNum) *  sizeof(float), Vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize * sizeof(GLuint), Indices, GL_STATIC_DRAW);
	checkGlError("Update VBO");
	LOGI("Updated VBO");
/*	char strBuffer[4];
		for(int i = 0 ; i < indiceSize; i++){
			sprintf(strBuffer, "%i", Indices[i]);
			LOGI(strBuffer);
		}
} */

bool setupGraphics(int w, int h) {
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	LOGI("setupGraphics(%d, %d)", w, h);
	gProgram = createProgram(gVertexShader, gFragmentShader);
	if (!gProgram) {
		LOGE("Could not create program.");
		return false;
	}
	mvp_a_positionHandle = glGetUniformLocation(gProgram, "modelViewMatrix");
	gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
	_colorSlot = glGetAttribLocation(gProgram, "SourceColor");
	glEnableVertexAttribArray(_colorSlot);
	LOGI("Found MVP Position Handle : %i", mvp_a_positionHandle);
	LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
			gvPositionHandle);
	checkGlError("glGetAttribLocation");
	//setupVBO();
	return true;
}

void setUniformMVP( GLuint Location, glm::vec3 const & Translate, glm::vec3 const & Rotate )
{
	glm::mat4 Projection =
			glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 ViewTranslate = glm::translate(
			glm::mat4(1.0f),
			Translate);
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 View = glm::rotate(ViewRotateY, Rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Model = glm::scale(
			glm::mat4(1.0f),
			glm::vec3(0.5f));
	glm::mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(
			Location, 1, GL_FALSE, glm::value_ptr(MVP));
}

float rotate = 0;
void renderFrame() {

	glClearColor(0,0,0, 1.0f);
	checkGlError("glClearColor");
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	checkGlError("glClear");
	//glBindBuffer(GL_ARRAY_BUFFER, modle->bufferID);
	glUseProgram(gProgram);
	checkGlError("glUseProgram");
	rotate+=0.5f;
	if(rotate > 360)
		rotate = 0;

	setUniformMVP(mvp_a_positionHandle, glm::vec3(0,0,-3), glm::vec3(0,270,rotate));
	if(modle->ready)
		modle->onDraw(gvPositionHandle);


/*	glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE,
			0, 0);
	checkGlError("glVertexAttribPointer");
//	glVertexAttribPointer(_colorSlot, 4, GL_FLOAT, GL_FALSE,
//			sizeof(float) * 7, (GLvoid*) (sizeof(float) * 3));
	//checkGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(gvPositionHandle);
	glDrawArrays(GL_TRIANGLES, 0, modle->vertexNum);
	checkGlError("draw arrays");*/




}

extern "C" {
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
JNIEXPORT int JNICALL Java_com_fbrs_electraengine_GL2JNILib_step(JNIEnv * env, jobject obj);
JNIEXPORT jstring JNICALL Java_com_fbrs_electraengine_GL2JNILib_jinterface(JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadModel(JNIEnv * env, jobject obj, jfloatArray verts, jint vertN, jfloatArray normals, jint normN);
};

JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	setupGraphics(width, height);
}
extern int JNIEngineFlag;
JNIEXPORT int JNICALL Java_com_fbrs_electraengine_GL2JNILib_step(JNIEnv * env, jobject obj)
{
	renderFrame();
	return JNIEngineFlag;
}

JNIEXPORT jstring JNICALL Java_com_fbrs_electraengine_GL2JNILib_jinterface(JNIEnv * env, jobject obj)
{
	const char* return_string = EngineStackpop()->string;
	return env->NewStringUTF(return_string);
}

JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadModel(JNIEnv * env, jobject obj, jfloatArray verts, jint vertN, jfloatArray normals, jint normN)
{
	jboolean *isCopy;
	jfloat* model = env->GetFloatArrayElements(verts, isCopy);
	int size =  vertN;
	Vertices = model;
	//Indices = (GLuint*)env->GetIntArrayElements(indices, isCopy);
	//	vertexSize = size;
	//indiceSize = indN;
	modle->onLoad(size, (float*)model);
//updateVBO();

	LOGI("Update Called");
}


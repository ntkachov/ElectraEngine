// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "EngineObject.h"
#include "Scene/Model.h"
#include "Scene/Scene.h"
#include "Engine/Engine.h"
#include "Helper.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

const char* gVertexShader,* gFragmentShader;

GLuint gProgram, gvPositionHandle,
gMVP, gModelMatrix,
gNomralMatrix, gvNormal,
gvTexture, gS_Texture,
gLightSource, gEye;

GLuint windowSize_h, windowSize_w;

GLuint frameBuffer[4];

bool EngineReady = false;

void setupHandles(){
	gMVP					= glGetUniformLocation(gProgram, "modelViewMatrix");
	gModelMatrix 			= glGetUniformLocation(gProgram, "ModelMatrix");
	gNomralMatrix 			=  glGetUniformLocation(gProgram, "NomralMatrix");
	gS_Texture			 	= glGetUniformLocation(gProgram, "s_texture");
	gLightSource			= glGetUniformLocation(gProgram, "lightSource");
	gEye					= glGetUniformLocation(gProgram, "eye");
//	gLightsCount 			= glGetUniformLocation(gProgram, "lightsCount");
//	fLightsCount 			= glGetUniformLocation(gProgram, "fragLightsCount");
	gvPositionHandle 		= glGetAttribLocation(gProgram, "vPosition");
	gvNormal				= glGetAttribLocation(gProgram, "vNormal");
	gvTexture 				= glGetAttribLocation(gProgram, "vTexture");

	checkGlError("glGetAttribLocation");
}

void initFrameBuffers(){
	glGenFramebuffers(1, &frameBuffer[0]);
	glGenRenderbuffers(2, &frameBuffer[1]);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, frameBuffer[1]);
	glBindRenderbuffer(GL_RENDERBUFFER, frameBuffer[2]);


	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, windowSize_w, windowSize_h);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, windowSize_w, windowSize_h);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, windowSize_w, windowSize_h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, frameBuffer[1]);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, frameBuffer[2]);


	GLuint frameBufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if( frameBufferStatus !=  GL_FRAMEBUFFER_COMPLETE){
		LOGE("Failed to make complete frame buffer object");
		printNum(frameBufferStatus);
	}
}

bool setupGraphics(int w, int h) {
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);
	windowSize_h = h; windowSize_w = w;
	LOGI("setupGraphics(%d, %d)", w, h);
	gProgram = createProgram(gVertexShader, gFragmentShader);
	if (!gProgram) {
		LOGE("Could not create program.");
		return false;
	}
	setupHandles();
	//initFrameBuffers();
	EngineStackpush("Engine Ready");

	EngineReady = true;
	return true;
}

void setUniformMVP( GLuint Location, glm::vec3 const & Translate, glm::vec3 const & Rotate )
{
	glm::mat4 Projection =
			glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);

	glm::mat4 LookAt = glm::lookAt(Translate, Rotate, glm::vec3(0,1,0));

	glm::mat4 MVP = Projection * LookAt;
	glUniformMatrix4fv(
			Location, 1, GL_FALSE, glm::value_ptr(MVP));
}

float rotate = 0;
void renderFrame(glm::vec3 const & rotateV, glm::vec3 const & translateV) {
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer[0]);
if(EngineReady){
	glClearColor(0,0,0, 1.0f);
	checkGlError("glClearColor");
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	checkGlError("glClear");
	glUseProgram(gProgram);
	checkGlError("glUseProgram");

	glUniform3f(gEye, translateV[0], translateV[1], translateV[2]);
	setUniformMVP(gMVP, translateV, rotateV + translateV);
	DrawScene(gvPositionHandle, gvNormal, gModelMatrix, gNomralMatrix, gvTexture, gS_Texture, gLightSource);
}
}

extern "C" {
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring vertexShader, jstring fragShader);
JNIEXPORT int JNICALL Java_com_fbrs_electraengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloatArray rotate, jfloatArray translate);
JNIEXPORT jstring JNICALL Java_com_fbrs_electraengine_GL2JNILib_jinterface(JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadModel(JNIEnv * env, jobject obj, jfloatArray verts, jfloatArray norms, jfloatArray UVs,
		jint vertN, jintArray polygroup, jfloatArray rotation, jfloatArray translate, jbyteArray texture, jint textureSize);
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadScene(JNIEnv * env, jobject obj, jint assetCount, jintArray assets);
JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadLight(JNIEnv * env, jobject obj, )
};

JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jstring vertexShader, jstring fragShader)
{
	jboolean *isCopy;
	gVertexShader = env->GetStringUTFChars(vertexShader, isCopy);
	gFragmentShader = env->GetStringUTFChars(fragShader, isCopy);
	setupGraphics(width, height);
}
extern int JNIEngineFlag;
JNIEXPORT int JNICALL Java_com_fbrs_electraengine_GL2JNILib_step(JNIEnv * env, jobject obj, jfloatArray rotate, jfloatArray translate)
{
	jboolean *isCopy;
	jfloat * rot = env->GetFloatArrayElements(rotate, isCopy);
	jfloat * trans = env->GetFloatArrayElements(translate, isCopy);
	renderFrame(glm::vec3((float)rot[0],(float) rot[1], (float)rot[2]), glm::vec3((float)trans[0], (float)trans[1], (float)trans[2]));
	env->ReleaseFloatArrayElements(rotate, rot, 0);
	env->ReleaseFloatArrayElements(translate, trans, 0);
	return EngineFlag();
}

JNIEXPORT jstring JNICALL Java_com_fbrs_electraengine_GL2JNILib_jinterface(JNIEnv * env, jobject obj)
{
	return env->NewStringUTF(EngineStackpop());
}

JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadModel(JNIEnv * env, jobject obj, jfloatArray verts, jfloatArray norms, jfloatArray UVs,
		jint vertN, jintArray polygroups, jfloatArray rotation, jfloatArray translate, jbyteArray texture, jint textureSize)
{
	jboolean *isCopy;
	jfloat* modelV = env->GetFloatArrayElements(verts, isCopy);
	jfloat* modelN = env->GetFloatArrayElements(norms, isCopy);
	jfloat* modelU = env->GetFloatArrayElements(UVs, isCopy);
	jfloat* rot = env->GetFloatArrayElements(rotation, isCopy);
	jfloat* trans = env->GetFloatArrayElements(translate, isCopy);
	jint* polys = env->GetIntArrayElements(polygroups, isCopy);
	GLubyte * textures =(GLubyte *) env->GetByteArrayElements(texture, isCopy);
	int size =  vertN;

	AddModel(size, (float*)modelV, (float*) modelN, (float*)modelU, (int*) polys, rot, trans, textures, textureSize);
	env->ReleaseFloatArrayElements(verts, modelV, 0);
	env->ReleaseFloatArrayElements(norms, modelN, 0);
	env->ReleaseFloatArrayElements(UVs, modelU, 0);
	env->ReleaseFloatArrayElements(rotation, rot, 0);
	env->ReleaseFloatArrayElements(translate, trans, 0);
	env->ReleaseIntArrayElements(polygroups, polys, 0);
	LOGI("Update Called");
}

JNIEXPORT void JNICALL Java_com_fbrs_electraengine_GL2JNILib_LoadScene(JNIEnv * env, jobject obj, jint assetCount, jintArray assets)
{
	jboolean *isCopy;
	//jint* scene = env->GetFloatArrayElements(verts, isCopy);

}


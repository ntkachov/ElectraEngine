#ifndef HELPER_H
#define HELPER_H

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

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
static void printFloat(float i){
	char strBuffer[4];
	sprintf(strBuffer, "%f", i);
	LOGI(strBuffer);
}

struct vec4{
	float x, y, z, w;
};

struct vec3{
	float x,y,z;
};

#endif

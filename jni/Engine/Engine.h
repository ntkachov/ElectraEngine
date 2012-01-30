#ifndef Engine_h
#define Engine_h


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

extern GLuint loadShader(GLenum shaderType, const char* pSource);
extern GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

#endif

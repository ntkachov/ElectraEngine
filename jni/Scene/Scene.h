#ifndef SCENE_H
#define SCENE_H
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <Helper.h>
extern void DrawScene(GLuint gvPositionHandle, GLuint normals, GLuint modelM,
		GLuint normM, GLuint texture, GLuint textureU, GLuint lights);
extern void LoadScene();
extern void AddModel(int vertexSize, float * Vertices, float * Normals, float * UV, int* polyGroups,
		float * position, float * rotation, GLubyte * texture, int size);
extern void AddLight(vec4 ambient, vec4 diffuse, vec4 specular, vec4 position);

#endif

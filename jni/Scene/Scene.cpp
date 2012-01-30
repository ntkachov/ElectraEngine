#include "Scene.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <vector>
#include "Model.h"
#include "Light.h"
using namespace std;

vector<Model> scene_models;
vector<Light> scene_lights;
void DrawScene(GLuint p, GLuint n, GLuint m, GLuint v, GLuint t, GLuint tu, GLuint lights){

	 glUniform3fv();
	 vector<Model>::iterator it;
	 for(it = scene_models.begin(); it < models.end(); it++){
		 if(it->ready)
			 it->onDraw(p,n,m,v,t, tu);
	 }
}

void LoadScene(){
}

void AddModel(int vertexSize, float * Vertices, float * Normals,
		float * UV, int * polys, float * position, float * rotation, GLubyte * texture, int size){
	Model m;
	m.onLoad(vertexSize, Vertices, Normals, UV, position, rotation, texture, size);
	scene_models.push_back(m);

}

void AddLight(vec4 ambient, vec4 diffuse, vec4 specular, vec4 position){
	Light l;
	l.ambient = ambient;
	l.diffuse = diffuse;
	l.position = position;
	l.specular = specular;
	scene_lights.push_back(m);
}



const int NUM_LIGHTS = 3;

struct gl_LightParams {
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 position;
};

uniform mat4 modelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NomralMatrix;
uniform vec4 diffuse, ambient, globalAmbient; 
uniform vec3 lightSource[NUM_LIGHTS];
uniform vec3 eye;
attribute vec4 vPosition;
attribute vec3 vNormal;
attribute vec2 vTexture;


varying vec2 f_texCoord;
varying vec3 normal;
varying glLightParams lights [NUM_LIGHTS];
varying vec3 halfVec[NUM_LIGHTS];


void main() {
	f_texCoord = vTexture;

	normal = normalize(NomralMatrix * vNormal);
	
	for(int i = 0; i < NUM_LIGHTS ; i++){
		lightDir[i] = normalize(lightSource[i]);
		halfVec[i] = eye - lightSource[i];
	}
	
	gl_Position = modelViewMatrix * ModelMatrix * vPosition;
}
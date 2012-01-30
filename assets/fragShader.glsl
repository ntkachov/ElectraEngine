precision mediump float;
struct gl_LightParams {
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 position;
};

struct gl_Material{
		vec4 emission;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
}

const int NUM_LIGHTS = 1;

uniform sampler2D s_texture;
uniform gl_Material modelMaterial;
varying vec2 f_texCoord;
varying vec3 normal;
varying glLightParams lights [NUM_LIGHTS];
varying vec3 halfVec[NUM_LIGHTS];



void main() {

	vec3 n,halfV;
	float NdotL,NdotHV;

	n = normalize(normal);
	vec4 texColor = texture2D(s_texture, f_texCoord); 
	float diffuse = 0.0;
	float specular = 0.0;
	for(int i = 0; i < NUM_LIGHTS; i++){
		NdotL = dot(n,lightDir[i]);
		diffuse += NdotL;
		halfV = normalize(halfVec[i]);
		NdotHV = dot(n,halfV);
		specular += clamp(.5 * pow(NdotHV, 32.0),0.0, 1.0);
	}
	gl_FragColor = texColor * vec4(diffuse) + vec4(specular);
}
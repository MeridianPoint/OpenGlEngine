#version 330



uniform float Ka;

uniform float Kd;

uniform float Ks;

//uniform float Shinness;

varying vec3 v;

varying vec3 N;
varying vec4 color;

//uniform sampler2D TextureUnit0;

vec3 phongDiffuse(){
	//
}

vec3 phongSpecular(){}

void main(void){

	
	vec3 L = normalize(gl_LightSource[0].position.xyz - v);
	vec3 E = normalize(-v);
	vec3 R = normalize(-reflect(L, N));
	vec4 ambient = (gl_FrontLightProduct[0].ambient*gl_FrontMaterial.ambient + gl_FrontLightProduct[1].ambient*gl_FrontMaterial.ambient)/2;
	vec4 diffuse = (gl_FrontLightProduct[0].diffuse*max(dot(N, L), 0.0) + gl_FrontLightProduct[1].diffuse*max(dot(N, L), 0.0))/2;
	diffuse = clamp(diffuse, 0.0, 1.0);
	vec4 specular = (gl_FrontLightProduct[0].specular*gl_FrontMaterial.specular*pow(max(dot(R, E), 0.0), 5.0) + gl_FrontLightProduct[1].specular*gl_FrontMaterial.specular*pow(max(dot(R, E), 0.0), 5.0))/2;
	specular = clamp(specular, 0.0, 1.0);
	if (dot(N, L) <= 0){
		specular = vec4(0.0,0.0,0.0,0.0);
	}

	gl_FragColor =  ambient*Ka+diffuse*Kd+specular*Ks;
}
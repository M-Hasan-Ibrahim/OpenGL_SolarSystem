#version 330 core	     // Minimal GL version support expected from the GPU

out vec4 color;	  // Shader output: the color response attached to this fragment

uniform vec3 camPos;
uniform vec3 lightPos;
uniform sampler2D textureSampler;
uniform vec3 objectColor;

uniform int isEmissive;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexture;


void main() {
	vec3 textureColor = texture(textureSampler, fTexture).rgb;
	vec3 base = textureColor * objectColor;

	if(isEmissive == 1){
		color = vec4(base, 1.0);
		return;
	}
	
	vec3 n = normalize(fNormal);
	vec3 l = normalize(lightPos - fPosition);
	vec3 v = normalize(lightPos - fPosition);
	vec3 r = reflect(-l, n);


	vec3 Ka = 0.15 * base;
	vec3 Kd = base;
	vec3 Ks = vec3(0.2);
	float shininess = 16.0;

	vec3 ambient = Ka;
	vec3 diffuse = Kd * max(dot(n, l), 0.0);
	vec3 specular = Ks * pow(max(dot(v, r), 0.0), shininess);

	color = vec4(ambient + diffuse, 1.0);
}

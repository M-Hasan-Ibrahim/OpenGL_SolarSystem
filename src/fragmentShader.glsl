#version 330 core	     // Minimal GL version support expected from the GPU

out vec4 color;	  // Shader output: the color response attached to this fragment

uniform vec3 camPos;
uniform vec3 lightPos;
uniform sampler2D textureSampler;
uniform vec3 objectColor;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexture;


void main() {
	
	vec3 n = normalize(fNormal);
	vec3 l = normalize(lightPos - fPosition);

	vec3 v = normalize(camPos - fPosition);
	vec3 r = reflect(-l, n);

	vec3 textureColor = texture(textureSampler, fTexture).rgb;
	vec3 base = textureColor * objectColor;
	

	vec3 Ka = 0.2 * base;
	vec3 Kd = base;
	vec3 Ks = vec3(0.6);
	float shininess = 32.0;

	vec3 ambient = Ka;
	vec3 diffuse = objectColor * Kd * max(dot(n, l), 0.0);
	vec3 specular = Ks * pow(max(dot(v, r), 0.0), shininess);

	color = vec4(ambient + diffuse + specular, 1.0); // build an RGBA from an RGB
}

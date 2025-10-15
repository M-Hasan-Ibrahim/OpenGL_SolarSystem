#version 330 core	     // Minimal GL version support expected from the GPU

out vec4 color;	  // Shader output: the color response attached to this fragment

uniform vec3 camPos;
uniform vec3 objectColor;

in vec3 fPosition;
in vec3 fNormal;


void main() {
	
	vec3 n = normalize(fNormal);
	vec3 l = normalize(vec3(1.0, 1.0, 0.0));

	vec3 v = normalize(camPos - fPosition);
	vec3 r = reflect(-l, n);

	vec3 Ka = vec3(0.2);
	vec3 Kd = vec3(1.0);
	vec3 Ks = vec3(0.8);
	float shininess = 32.0;

	vec3 ambient = Ka;
	vec3 diffuse = objectColor * Kd * max(dot(n, l), 0.0);
	vec3 specular = Ks * pow(max(dot(v, r), 0.0), shininess);

	color = vec4(ambient + diffuse + specular, 1.0); // build an RGBA from an RGB
}

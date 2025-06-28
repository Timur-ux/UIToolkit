// vertex

#version 330 core 

uniform mat4 model;

layout (location = 0) in vec3 coord;
layout (location = 1) in vec3 color;

out vec3 fgColor;

void main() {
	gl_Position = model * vec4(coord, 1.0);
	fgColor = color;
}

// fragment

#version 330 core

out vec4 outColor;
in vec3 fgColor;

void main() {
	outColor = vec4(fgColor, 1.0);
}



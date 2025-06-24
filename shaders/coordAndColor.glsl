// vertex

#version 330 core 

layout (location = 0) in vec3 coord;
layout (location = 1) in vec4 color;

out vec4 fgColor;

void main() {
	gl_Position = vec4(coord, 1.0);
	fgColor = color;
}

// fragment

#version 330 core

out vec4 outColor;
in vec4 fgColor;

void main() {
	outColor = fgColor;
}


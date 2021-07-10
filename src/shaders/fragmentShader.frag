#version 330 core 

out vec4 FragColor; 

uniform vec4 vertexColor;
uniform int useTex;
in vec2 texCoord;

uniform sampler2D tex0;

void main() 
{ 
	FragColor = useTex == 1 ? texture(tex0, texCoord) : vertexColor;
}
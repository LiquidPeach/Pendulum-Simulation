#version 330 core 

out vec4 FragColor; 

uniform vec4 vertexColor;
uniform int  useTex;
in vec2      texCoord;

uniform sampler2D tex0;

void main() 
{ 
	// The ball will have a texture and the rope will not. Using the uniform "useTex", I can tell the fragment shader whether there
    // will be a texture in use or not whenever I want to draw. (Thank you Rid from theCherno's Discord server for the idea)
	FragColor = useTex == 1 ? texture(tex0, texCoord) : vertexColor;
}
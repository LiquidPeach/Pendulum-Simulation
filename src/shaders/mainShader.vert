#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoord;

uniform mat4 u_MvpRope;
uniform mat4 u_MvpBall;
uniform int  rope;

void main()
{
	// so the position of the Ball and Rope can be altered seperately
	gl_Position = rope == 1 ? (u_MvpRope * aPos) : (u_MvpBall * aPos);
	texCoord = aTex;
}
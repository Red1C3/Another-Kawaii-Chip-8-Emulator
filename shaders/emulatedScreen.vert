#version 330
layout(location=0) in vec2 pos;
out vec2 pixPos;
void main(){
	vec2 posScreenSpace=pos;
	pixPos=pos;
	posScreenSpace.x/=64;
	posScreenSpace.y/=32;
	posScreenSpace=posScreenSpace*2;
	posScreenSpace-=1.0;
	gl_Position=vec4(posScreenSpace,0,1);
}
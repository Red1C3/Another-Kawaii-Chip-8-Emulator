#version 330
layout(location=0) in vec2 pos;
out vec2 outPos;
void main(){
	outPos=pos;
    gl_Position=vec4(pos,0,1);
}
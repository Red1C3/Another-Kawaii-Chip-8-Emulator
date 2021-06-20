#version 330
out vec4 color;
in vec2 pixPos;
void main(){
	color=vec4(pixPos/100,0,1);
}
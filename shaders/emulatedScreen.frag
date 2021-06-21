#version 330
out vec4 color;
in vec2 pixPos;
layout(shared) uniform Block{
	int pixels[2048];
};
void main(){
	int pixState;
	pixState=pixels[32*int(pixPos.x)+int(pixPos.y)];
	color=vec4(pixState,pixState,pixState,1);
}
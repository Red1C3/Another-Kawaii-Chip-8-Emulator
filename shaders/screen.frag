#version 330
out vec4 color;
in vec2 outPos;
uniform sampler2D tex;
void main(){
	vec2 uv=outPos+vec2(1,1);
	uv=uv/2;
    color=texture(tex,uv);
}
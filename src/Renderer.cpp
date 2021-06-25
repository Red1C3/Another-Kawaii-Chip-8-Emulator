/*MIT License

Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include<Renderer.h>
using namespace akcemu;
using namespace glm;
Renderer::Renderer(){}
Renderer& Renderer::instance(){
    static Renderer renderer;
    return renderer;
}
void Renderer::init(int height,int width){
    this->wWidth=width;
    this->wHeight=height;
    
    if(!glfwInit()){
        LOG.error("Failed to init glfw");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    window=glfwCreateWindow(width,height,"AKCEmu",nullptr,nullptr);
    if (window==nullptr){
        LOG.error("Failed to create window");
    }
    glfwMakeContextCurrent(window);
    glewExperimental=true;
    if(glewInit()!=GLEW_OK){
        LOG.error("Falied to init glew");
    }
    glGenTextures(1,&renderTexture);
    glBindTexture(GL_TEXTURE_2D,renderTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,64,32,0,GL_RGB,GL_FLOAT,nullptr);
    glGenFramebuffers(1,&renderFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,renderFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,renderTexture,0);
    glGenVertexArrays(1,&emulatedQuadVAO);
    glBindVertexArray(emulatedQuadVAO);
    glGenBuffers(1,&emulatedQuadVBO);
    glGenBuffers(1,&emulatedQuadEBO);
    glBindBuffer(GL_ARRAY_BUFFER,emulatedQuadVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,emulatedQuadEBO);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(short),emulatedQuad,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(short),emulatedQuadIndices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_SHORT,GL_FALSE,0,0);
    glGenBuffers(1,&pixelsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER,pixelsUBO);
    glBufferData(GL_UNIFORM_BUFFER,32*64*sizeof(GLint),pixels,GL_STATIC_DRAW);
    emulatedQuadShader=createShader("../shaders/emulatedScreen.vert","../shaders/emulatedScreen.frag");
    glUseProgram(emulatedQuadShader);
    GLuint pixelsUBOIndex=glGetUniformBlockIndex(emulatedQuadShader,"Block");
    glUniformBlockBinding(emulatedQuadShader,pixelsUBOIndex,0);
    glBindBufferRange(GL_UNIFORM_BUFFER,0,pixelsUBO,0,32*64*sizeof(GLint));
    glGenVertexArrays(1,&screenQuadVAO);
    glBindVertexArray(screenQuadVAO);
    glGenBuffers(1,&screenQuadVBO);
    glGenBuffers(1,&screenQuadEBO);
    glBindBuffer(GL_ARRAY_BUFFER,screenQuadVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,screenQuadEBO);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(short),screenQuad,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(short),screenQuadIndices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_SHORT,GL_FALSE,0,0);
    screenQuadShader=createShader("../shaders/screen.vert","../shaders/screen.frag");
    glClearColor(0,0,0,1);
}
void Renderer::render(){
    /*First Pass Renders to a 64x32 texture*/
    glBufferSubData(GL_UNIFORM_BUFFER,0,32*64*sizeof(GLint),pixels);
    glBindFramebuffer(GL_FRAMEBUFFER,renderFramebuffer);
    glViewport(0,0,64,32);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(emulatedQuadVAO);
    glUseProgram(emulatedQuadShader);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
    /*Second Pass Renders to screen*/
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,wWidth,wHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(screenQuadVAO);
    glUseProgram(screenQuadShader);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
GLuint Renderer::createShader(const char* vertexShaderPath,const char* fragmentShaderPath){
    auto vertexShaderCode=readBin(vertexShaderPath);
    auto fragmentShaderCode=readBin(fragmentShaderPath);
    auto program=glCreateProgram();
    GLuint vertexShader,fragmentShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    int size=vertexShaderCode.size();
    char* data=vertexShaderCode.data();
    glShaderSource(vertexShader,1,&data,&size);
    glCompileShader(vertexShader);
    GLint Result=GL_FALSE;
    int infoLogLength;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&Result);
    glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&infoLogLength);
    if (infoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		LOG.log(VertexShaderErrorMessage.data());
	}
    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    size=fragmentShaderCode.size();
    data=fragmentShaderCode.data();
    glShaderSource(fragmentShader,1,&data,&size);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&Result);
    glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&infoLogLength);
    if (infoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		LOG.log(VertexShaderErrorMessage.data());
	}
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		LOG.log(programErrorMessage.data());
	}
    glDetachShader(program,vertexShader);
    glDetachShader(program,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
bool Renderer::setPixel(int x,int y){
    if(x>63){
        x-=63;
    }else if(x<0){
        x+=63;
    }
    if(y>31){
        y-=31;
    }else if(y<0){
        y+=31;
    }
    x--;
    y=31-y;
    pixels[x][y]^=1;
    return !pixels[x][y];
}
void Renderer::clearScreen(){
    for(int i=0;i<64;++i)
        for(int j=0;j<32;++j)
            pixels[i][j]=0;
}
GLFWwindow* Renderer::getWindow(){
    return window;
}
void Renderer::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
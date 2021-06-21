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

}
void Renderer::render(){
    glBindFramebuffer(GL_FRAMEBUFFER,renderFramebuffer);
    glViewport(0,0,64,32);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(emulatedQuadVAO);
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
GLFWwindow* Renderer::getWindow(){
    return window;
}
void Renderer::terminate(){
    LOG.log("OpenGL exited with code:");
    LOG.log(std::to_string(glGetError()));
    glfwDestroyWindow(window);
    glfwTerminate();
}
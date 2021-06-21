#pragma once
#define RENDERER  Renderer::instance()
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<Log.h>
#include<Common.h>
namespace akcemu{
    class Renderer{
        Renderer();
        bool isInitialized=false;
        GLFWwindow* window;
        int wHeight,wWidth;
        GLuint renderTexture,renderFramebuffer,
            emulatedQuadVAO,emulatedQuadVBO,emulatedQuadEBO,
            screenQuadVAO,screenQuadVBO,screenQuadEBO;
        GLint pixels[64][32];
        short emulatedQuad[8]={0,0,64,0,0,32,64,32};
        short emulatedQuadIndices[6]={0,1,2,2,1,3};
        short screenQuad[8]={-1,-1,-1,1,1,-1,1,1};
        short screenQuadIndices[6]={0,2,1,3,1,2};
        GLuint emulatedQuadShader,screenQuadShader;
        GLuint pixelBufferLoc;
        GLuint pixelsUBO;
    public:
        static Renderer& instance();
        void init(int height,int width);
        void render();
        void terminate();
        GLFWwindow* getWindow();
        static GLuint createShader(const char* vertexShaderPath,const char* fragmentShaderPath);
    };
}
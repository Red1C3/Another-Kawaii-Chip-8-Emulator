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
        bool setPixel(int x,int y);
        void clearScreen();
        static GLuint createShader(const char* vertexShaderPath,const char* fragmentShaderPath);
    };
}
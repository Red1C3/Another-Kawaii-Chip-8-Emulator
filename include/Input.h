#pragma once
#define INPUT Input::instance()
#include<GLFW/glfw3.h>
#include<Log.h>
namespace akcemu{
    class Input{
        Input();
    public:
        static Input& instance();
        void init(GLFWwindow* window,bool keys[16],bool* paused);
        bool* keys;
        void pause(unsigned char* registerX);
        bool* paused;
        unsigned char* resumeRegister;
    };
}
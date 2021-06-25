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
#include<Input.h>
using namespace akcemu;
static inline void keys_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    int keyIndex;
    switch (key)
    {
    case GLFW_KEY_1:
        keyIndex=0;
        break;
    case GLFW_KEY_2:
        keyIndex=1;
        break;
    case GLFW_KEY_3:
        keyIndex=2;
        break;
    case GLFW_KEY_4:
        keyIndex=3;
        break;
    case GLFW_KEY_Q:
        keyIndex=4;
        break;
    case GLFW_KEY_W:
        keyIndex=5;
        break;
    case GLFW_KEY_E:
        keyIndex=6;
        break;
    case GLFW_KEY_R:
        keyIndex=7;
        break;
    case GLFW_KEY_A:
        keyIndex=8;
        break;
    case GLFW_KEY_S:
        keyIndex=9;
        break;
    case GLFW_KEY_D:
        keyIndex=10;
        break;
    case GLFW_KEY_F:
        keyIndex=11;
        LOG.log("Respects Paid");
        break;
    case GLFW_KEY_Z:
        keyIndex=12;
        break;
    case GLFW_KEY_X:
        keyIndex=13;
        break;
    case GLFW_KEY_C:
        keyIndex=14;
        break;
    case GLFW_KEY_V:
        keyIndex=15;
        break;
    default:
        break;
    }
    if(action==GLFW_PRESS){
        INPUT.keys[keyIndex]=true;
        if(INPUT.paused[0]==true){
            INPUT.resumeRegister[0]=keyIndex;
            INPUT.paused[0]=false;
        }
    }else if(action==GLFW_RELEASE){
        INPUT.keys[keyIndex]=false;
    }
}
void Input::init(GLFWwindow* window,bool keys[16],bool* paused){
    glfwSetKeyCallback(window,keys_callback);
    this->keys=keys;
    this->paused=paused;
}
Input& Input::instance(){
    static Input input;
    return input;
}
Input::Input(){}
void Input::pause(unsigned char* registerX){
    this->resumeRegister=registerX;
    paused[0]=true;
    LOG.log("Paused");
}
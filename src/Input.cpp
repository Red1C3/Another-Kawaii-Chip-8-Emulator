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
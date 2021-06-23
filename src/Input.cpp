#include<Input.h>
using namespace akcemu;
static inline void keys_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action==GLFW_PRESS){
        switch (key)
        {
        case GLFW_KEY_1:
            
            break;
        case GLFW_KEY_2:
            break;
        case GLFW_KEY_3:
            break;
        case GLFW_KEY_4:
            break;
        case GLFW_KEY_Q:
            break;
        case GLFW_KEY_W:
            break;
        case GLFW_KEY_E:
            break;
        case GLFW_KEY_R:
            break;
        case GLFW_KEY_A:
            break;
        case GLFW_KEY_S:
            break;
        case GLFW_KEY_D:
            break;
        case GLFW_KEY_F:
            LOG.log("Respects Paid");
            break;
        case GLFW_KEY_Z:
            break;
        case GLFW_KEY_X:
            break;
        case GLFW_KEY_C:
            break;
        case GLFW_KEY_V:
            break;
        default:
            break;
        }
    }
    
}
void akcemu::initInput(GLFWwindow* window){
    glfwSetKeyCallback(window,keys_callback);
}
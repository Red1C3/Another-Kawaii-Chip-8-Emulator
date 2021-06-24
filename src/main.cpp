#include<Log.h>
#include<Renderer.h>
#include<Input.h>
#include<Speaker.h>
#include<Emulator.h>
using namespace akcemu;
int main(){
    RENDERER.init(640,1280);
    initInput(RENDERER.getWindow());
    SPEAKER.init();
    EMULATOR.init(0,"../Assets/pong.ch8");
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
        EMULATOR.cycle();
    }
    RENDERER.terminate();
}
#include<Log.h>
#include<Renderer.h>
#include<Input.h>
#include<Speaker.h>
#include<Emulator.h>
using namespace akcemu;
int main(){
    RENDERER.init(640,1280);
    bool keys[16];
    SPEAKER.init();
    EMULATOR.init(10,"../Assets/pong.ch8",keys);
    INPUT.init(RENDERER.getWindow(),keys,&EMULATOR.paused);
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
        EMULATOR.cycle();
    }
    RENDERER.terminate();
}
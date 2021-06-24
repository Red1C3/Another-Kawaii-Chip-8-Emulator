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
    EMULATOR.init(700/60,"../Assets/pong.ch8",keys);
    INPUT.init(RENDERER.getWindow(),keys,&EMULATOR.paused);
    float startTime=glfwGetTime();
    float timeStamp;
    bool wait=false;
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
        if(!wait){
            EMULATOR.cycle();
            startTime=glfwGetTime();
            wait=true;
        }else if(glfwGetTime()-startTime>1.0f/60.0f){
            wait=false;
        }
    }
    RENDERER.terminate();
}
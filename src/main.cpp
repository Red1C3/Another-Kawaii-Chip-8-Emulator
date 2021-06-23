#include<Log.h>
#include<Renderer.h>
#include<Input.h>
using namespace akcemu;
int main(){
    RENDERER.init(640,1280);
    initInput(RENDERER.getWindow());
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
       RENDERER.render();
    }
    RENDERER.terminate();
}
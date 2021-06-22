#include<Log.h>
#include<Renderer.h>
using namespace akcemu;
int main(){
    RENDERER.init(640,1280);
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
       RENDERER.render();
    }
    RENDERER.terminate();
}
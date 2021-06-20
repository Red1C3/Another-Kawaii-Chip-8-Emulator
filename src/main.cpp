#include<Log.h>
#include<Renderer.h>
using namespace akcemu;
int main(){
    RENDERER.init(320,640);
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
       RENDERER.render();
    }
    RENDERER.terminate();
}
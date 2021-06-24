#include<Speaker.h>
using namespace akcemu;
using namespace sf;
Speaker::Speaker(){}
Speaker& Speaker::instance(){
    static Speaker speaker;
    return speaker;
}
void Speaker::init(){
    if(!buffer.loadFromFile("../Assets/beep.ogg")){
        LOG.error("Failed to load audio file");
    }
    sounder.setBuffer(buffer);
}
void Speaker::play(){
    sounder.play();
}
void Speaker::stop(){
    sounder.stop();
}
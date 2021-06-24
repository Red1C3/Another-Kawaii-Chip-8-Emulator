#include<Emulator.h>
using namespace akcemu;
using namespace std;
Emulator::Emulator(){}
Emulator& Emulator::instance(){
    static Emulator emulator;
    return emulator;
}
void Emulator::init(int executionSpeed,string romPath){
    this->executionSpeed=executionSpeed;
    loadHexaSprites();
    loadRomIntoRam(romPath);
}
void Emulator::loadHexaSprites(){
    unsigned char sprites[]={
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    for(int i=0;i<80;++i){
        memory[i]=sprites[i];
    }
}
void Emulator::loadRomIntoRam(string romPath){
    auto rom=readBin(romPath.c_str());
    LOG.log("ROM size is...");
    LOG.log(to_string(rom.size()));
    for(uint32_t i=0;i<rom.size();++i)
        memory[0x200+i]=rom[i];
}
void Emulator::dumpMemory(){
    LOG.log("Dumping memory...");
    for(int i=0;i<4096;++i)
        LOG.log(std::to_string(memory[i]));
    LOG.log("Finished dumping memory");
}
void Emulator::cycle(){
    
    for(int i=0;i<executionSpeed;++i){
        if(!paused){
            unsigned short opcode=(memory[programCounter]<<8|memory[programCounter+1]);
            executeInstruction(opcode);
        }
    }
    if(!paused){
        updateTimers();
    }
    playSound();
    RENDERER.render();
    
}
void Emulator::executeInstruction(unsigned short opcode){
    
    programCounter+=2;
}
void Emulator::updateTimers(){
    timersTicker++;
    if(timersTicker>=60){
        if(delayTimer>0){
            delayTimer--;
        }
        if(soundTimer>0){
            soundTimer--;
        }
        timersTicker=0;
        LOG.log("TICKED!");
    }
}
void Emulator::playSound(){
    if(soundTimer>0){
        SPEAKER.play();
    }else{
        SPEAKER.stop();
    }
}
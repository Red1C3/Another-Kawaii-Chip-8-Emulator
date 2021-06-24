#include<Emulator.h>
using namespace akcemu;
using namespace std;
Emulator::Emulator(){}
Emulator& Emulator::instance(){
    static Emulator emulator;
    return emulator;
}
void Emulator::init(int executionSpeed,string romPath,bool keys[16]){
    this->executionSpeed=executionSpeed;
    this->keys=keys;
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
    unsigned char x=(opcode&0x0F00)>>8;
    unsigned char y=(opcode&0x00F0)>>4;
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (opcode) {
            case 0x00E0:
                RENDERER.clearScreen();
                break;
            case 0x00EE:
                programCounter=emuStack.top();
                emuStack.pop();
                break;
        }

        break;
    case 0x1000:
        programCounter=(opcode&0xFFF);
        break;
    case 0x2000:
        emuStack.push(programCounter);
        programCounter=(opcode&0xFFF);
        break;
    case 0x3000:
        if(registers[x]==(opcode&0xFF)){
            programCounter+=2;
        }
        break;
    case 0x4000:
        if(registers[x]!=(opcode&0xFF)){
            programCounter+=2;
        }
        break;
    case 0x5000:
        if(registers[x]==registers[y]){
            programCounter+=2;
        }
        break;
    case 0x6000:
        registers[x]=(opcode&0xFF);
        break;
    case 0x7000:
        registers[x]+=(opcode&0xFF);
        break;
    case 0x8000:
        switch (opcode & 0xF) {
            case 0x0:
                registers[x]=registers[y];
                break;
            case 0x1:
                registers[x]|=registers[y];
                break;
            case 0x2:
                registers[x]&=registers[y];
                break;
            case 0x3:
                registers[x]^=registers[y];
                break;
            case 0x4:
            {
                unsigned int sum=(unsigned int)registers[x]+(unsigned int)registers[y]; //watch for conversions
                registers[0xF]=0;
                if(sum>0xFF){
                    registers[0xF]=1;
                }
                registers[x]=sum&0xFF;
                break;
            }
            case 0x5:
                registers[0xF]=0;
                if(registers[x]>registers[y]){
                    registers[0xF]=1;
                }
                registers[x]-=registers[y];
                break;
            case 0x6:
                registers[0xF]=(registers[x]&0x1);
                registers[x]>>=1;
                break;
            case 0x7:
                registers[0xF]=0;
                if(registers[y]>registers[x]){
                    registers[0xF]=1;
                }
                registers[x]=registers[y]-registers[x];
                break;
            case 0xE:
                registers[0xF]=((registers[x]&0x80)>>7);
                registers[x]<<=1;
                break;
        }

        break;
    case 0x9000:
        if(registers[x]!=registers[y]){
            programCounter+=2;
        }
        break;
    case 0xA000:
        registerI=(opcode&0xFFF);
        break;
    case 0xB000:
        programCounter=(opcode&0xFFF)+registers[0]; //watch for conversions
        break;
    case 0xC000:
    {
        unsigned char rand=std::rand()%256;
        registers[x]=(rand&(opcode&0xFF));
        break;
    }
    case 0xD000:
    {
        unsigned short width=8;
        unsigned short height=(opcode&0xF);
        registers[0xF]=0;
        for(unsigned short row=0;row<height;++row){
            unsigned char sprite=memory[registerI+row];
            for(unsigned char col=0;col<width;++col){
                if((sprite&0x80)>0){
                    if(RENDERER.setPixel(registers[x]+col,registers[y]+row)){
                        registers[0xF]=1;
                    }
                }
                sprite<<=1;
            }
        }
        break;
    }
    case 0xE000:
        switch (opcode & 0xFF) {
            case 0x9E:
                if(keys[registers[x]]){
                    programCounter+=2;
                }
                break;
            case 0xA1:
                if(!keys[registers[x]]){
                    programCounter+=2;
                }
                break;
        }

        break;
    case 0xF000:
        switch (opcode & 0xFF) {
            case 0x07:
                registers[x]=delayTimer;
                break;
            case 0x0A:
                INPUT.pause(&registers[x]);
                break;
            case 0x15:
                delayTimer=registers[x];
                break;
            case 0x18:
                soundTimer=registers[x];
                break;
            case 0x1E:
                registerI+=(unsigned short)registers[x]; //watch for conversions
                break;
            case 0x29:
                registerI=(unsigned short) registers[x]*5; //watch for conversions
                break;
            case 0x33:
                memory[registerI]=registers[x]/100;
                memory[registerI+1]=(registers[x]%100)/10;
                memory[registerI+2]=registers[x]%10;
                break;
            case 0x55:
                for(int i=0;i<=x;++i){
                    memory[registerI+i]=registers[i];
                }
                break;
            case 0x65:
                for(int i=0;i<=x;++i){
                    registers[i]=memory[registerI+i];
                }
                break;
        }

        break;

    default:
        LOG.error("Unknown instruction:"+std::to_string(opcode));
        break;
    }
}
void Emulator::updateTimers(){
    
        if(delayTimer>0){
            delayTimer--;
        }
        if(soundTimer>0){
            soundTimer--;
        }
    
}
void Emulator::playSound(){
    if(soundTimer>0){
        SPEAKER.play();
    }else{
        SPEAKER.stop();
    }
}
#pragma once
#define EMULATOR Emulator::instance()
#include<stack>
#include<Log.h>
#include<Common.h>
#include<Renderer.h>
#include<Speaker.h>
#include<Input.h>
namespace akcemu{
    class Emulator{
        Emulator();
        unsigned char memory[4096];
        unsigned char registers[16];
        unsigned char delayTimer=0,soundTimer=0;
        unsigned short registerI,programCounter=0x200;
        std::stack<unsigned short> emuStack;
        int executionSpeed;
        void loadHexaSprites();
        void loadRomIntoRam(std::string romPath);
        void executeInstruction(unsigned short opcode);
        void updateTimers();
        void playSound();
        int timersTicker=0;
        bool* keys;
    public:
        bool paused=false;
        static Emulator& instance();
        void init(int executionSpeed,std::string romPath,bool keys[16]);
        void dumpMemory();
        void cycle();
    };
}
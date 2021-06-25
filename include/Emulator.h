/*MIT License

Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
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
        bool* keys;
    public:
        bool paused=false;
        static Emulator& instance();
        void init(int executionSpeed,std::string romPath,bool keys[16]);
        void dumpMemory();
        void cycle();
    };
}
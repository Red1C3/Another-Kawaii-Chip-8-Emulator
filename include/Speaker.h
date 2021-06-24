#pragma once
#define SPEAKER Speaker::instance()
#include<SFML/Audio.hpp>
#include<Log.h>
namespace akcemu{
    class Speaker{
        Speaker();
        sf::SoundBuffer buffer;
        sf::Sound sounder;
    public:
        static Speaker& instance();
        void init();
        void play();
        void stop();
    };
}
#pragma once
#define LOG Log::instance()
#include<string>
#include<fstream>
namespace akcemu{
    class Log{
        Log();
        std::fstream fileStream;
    public:
        static Log& instance();
        void log(std::string str);
        void error(std::string str,bool fatal=true);
        void close();
    };
}

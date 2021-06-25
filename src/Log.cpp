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
#include<Log.h>
using namespace akcemu;
using namespace std;
Log::Log(){
    fileStream=fstream("../log.txt",ios::out);
    if(!fileStream.is_open()){
        throw exception();
    }
}
Log& Log::instance(){
    static Log log;
    return log;
}
void Log::log(string str){
    fileStream.write("LOG:",4);
    fileStream.write(str.c_str(),str.size());
    fileStream.write("\n",1);
}
void Log::error(string str,bool fatal){
    fileStream.write("ERR:",4);
    fileStream.write(str.c_str(),str.size());
    fileStream.write("\n",1);
    if(fatal){
        close();
        throw exception();
    }
}
void Log::close(){
    fileStream.flush();
    fileStream.close();
}
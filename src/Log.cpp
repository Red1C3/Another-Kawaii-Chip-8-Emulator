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